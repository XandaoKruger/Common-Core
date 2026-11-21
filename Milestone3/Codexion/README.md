*This project has been created as part of the 42 curriculum by acano-kr.*
 
# Codexion
 
## Description
 
Codexion is a concurrency simulation written in C with POSIX threads. `N` coders sit in a circle, and between every two neighbours there is one USB dongle. Each coder repeats the same cycle:
 
1. **compile**: needs *both* adjacent dongles,
2. **debug**,
3. **refactor**.
A coder suffers **burnout** if `time_to_burnout` ms pass without *starting* a compile (counted from the start of the previous compile, or from the start of the simulation). After a dongle is released it cannot be taken again for `dongle_cooldown` ms. The simulation ends when every coder has compiled `number_of_compiles_required` times, or when the first burnout happens.
 
The goal is to share the dongles without deadlock, to avoid starving anyone, to detect a burnout with a precision of a few milliseconds, and to keep the log readable. Waiting requests for a dongle are served by a priority queue implemented from scratch (a binary min-heap), under one of two schedulers:
 
- **FIFO**: the oldest request is served first.
- **EDF** (earliest deadline first): the request of the coder with the nearest burnout deadline (`last_compile_start + time_to_burnout`) is served first.
## Instructions
 
### Build
 
```
make          # builds ./codexion
make clean    # removes object files
make fclean   # removes objects and binaries
make re       # fclean + build
```
 
Compiled with `cc -Wall -Wextra -Werror -pthread`. Development helpers (not required by the subject):
 
```
make norm                              # norminette on src/ and include/
make val  ARGS="5 3000 200 200 200 3 100 edf"   # valgrind (leaks)
make hel  ARGS="5 3000 200 200 200 3 100 edf"   # valgrind --tool=helgrind
```
 
Use generous timings under valgrind/helgrind: they slow the program down a lot and tight burnouts then fail for reasons unrelated to the logic.
 
### Run
 
```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```
 
All times are in milliseconds. `scheduler` is `fifo` or `edf`.
 
| argument | accepted values |
|---|---|
| `number_of_coders` | integer >= 1 |
| `time_to_burnout` | integer >= 1 |
| `time_to_compile`, `time_to_debug`, `time_to_refactor`, `dongle_cooldown` | integer >= 0 |
| `number_of_compiles_required` | integer >= 0 |
| `scheduler` | exactly `fifo` or `edf` |
 
Every numeric argument must be made only of digits and fit in an `int`. Anything else prints a usage message on `stderr` and exits with status 1.
 
Log format (one line per event, timestamp in ms since the start of the simulation):
 
```
timestamp_in_ms coder_id has taken a dongle
timestamp_in_ms coder_id is compiling
timestamp_in_ms coder_id is debugging
timestamp_in_ms coder_id is refactoring
timestamp_in_ms coder_id burned out
```
 
Example with a single coder (there is only one dongle, so it can never compile):
 
```
$ ./codexion 1 800 200 200 200 5 0 fifo
0 1 has taken a dongle
801 1 burned out
```
 
## Technical choices
 
| file | content |
|---|---|
| `parse.c` | argument validation (`parse_num`, `parse_sched`, `parse_args`) |
| `time.c` | `get_time_ms`, `ms_sleep` (interruptible sleep) |
| `log.c` | serialized `print_log`, `is_stopped` |
| `init.c`, `cleanup.c` | allocation and destruction of coders, dongles, mutexes, heaps |
| `coder.c` | coder routine (the compile / debug / refactor cycle) |
| `dongle.c`, `dongle_queue.c` | taking and releasing dongles, per-dongle request queue |
| `heap.c`, `heap_utils.c` | binary min-heap used as priority queue |
| `monitor.c`, `monitor_utils.c` | burnout detection, end of simulation, waking sleepers |
| `launch.c` | thread creation and joining |
 
Coder `i` uses dongle `i` and dongle `(i + 1) % N`. Everything shared lives in a single `t_sim` structure that is passed to the threads: there are no global variables.
 
## Blocking cases handled
 
### Deadlock prevention (Coffman's conditions)
 
A deadlock needs four conditions at once: mutual exclusion, hold and wait, no preemption and circular wait.
 
- *Mutual exclusion* is inherent to the problem (a dongle is used by one coder at a time).
- *No preemption*: a coder keeps its dongles until it finishes compiling; this is also inherent.
- *Hold and wait* is **not** removed: a coder holds its first dongle while waiting for the second.
- *Circular wait* is **removed**: every coder takes the dongle with the **lowest index first** and the other one second. A global order on the resources makes a cycle of waiters impossible.
Dongles are taken one after the other under that order, so no coder ever waits for a dongle with a lower index than the one it already holds.
 
### Starvation prevention
 
Every dongle has its own queue of pending requests (a min-heap). A coder may take a dongle only if it is free, its cooldown is over **and** the coder's request is at the top of that dongle's queue. Ties on the key are broken by the coder id, which makes the order deterministic.
 
- FIFO key: a per-dongle arrival counter.
- EDF key: `last_compile_start + time_to_burnout` of the requesting coder.
### Cooldown handling
 
When a dongle is released, `available_at = now + dongle_cooldown` is stored under the dongle mutex. A waiter whose dongle is free but still cooling down sleeps with `pthread_cond_timedwait` until the **absolute** instant `available_at`, so it neither polls nor oversleeps. When the cooldown is over and it is the coder's turn, the wait is skipped; this closes a window in which the clock could change between two readings and leave a coder asleep on a free dongle.
 
### Precise burnout detection
 
A dedicated monitor thread wakes up every millisecond, and for each coder reads `last_compile_start` and `compile_count` under the coder's mutex. If `now - last_compile_start >= time_to_burnout` and the coder has not finished its compiles, the burnout is declared. Measured on this implementation, `burned out` was printed 0 to 6 ms after the deadline with 5 coders and 0 to 1 ms with 200 coders (limit in the subject: 10 ms). Coders that already compiled `number_of_compiles_required` times are ignored, so a finished coder never "burns out".
 
### Log serialization
 
All output goes through one function guarded by `log_lock`. The timestamp is computed **inside** the lock, so lines come out in timestamp order and never interleave. The `stop` flag is protected by the same mutex: the monitor sets it and prints `burned out` in the same critical section, so no message can appear after the burnout.
 
### Lost wake-ups and clean termination
 
When the simulation stops, coders may be asleep in `pthread_cond_wait` / `timedwait` on a dongle. The monitor sets `stop`, and then, for **every** dongle, locks its mutex, broadcasts its condition variable and unlocks. Locking before the broadcast matters: a coder checks `stop` while holding the dongle mutex and only releases it by entering the wait, so it either sees `stop = 1` or is already asleep when the broadcast arrives. `ms_sleep` sleeps in slices of 0.5 ms and checks `stop` on each slice, so coders asleep in a phase also leave quickly. All threads are joined before any memory is freed.
 
### Single coder
 
With one coder there is one dongle (left and right are the same). It can never hold two dongles, so it takes one, waits, and the monitor reports its burnout at `time_to_burnout`.
 
## Thread synchronization mechanisms
 
| primitive | where | protects |
|---|---|---|
| `pthread_mutex_t lock` (one per dongle) | `t_dongle` | `is_taken`, `available_at`, `arrivals`, the request heap |
| `pthread_cond_t cond` (one per dongle) | `t_dongle` | waiting coders: signalled by `release_dongle` and by the monitor on stop |
| `pthread_mutex_t lock` (one per coder) | `t_coder` | `last_compile_start`, `compile_count` (written by the coder, read by the monitor) |
| `pthread_mutex_t log_lock` | `t_sim` | `stdout` output and the `stop` flag |
 
Lock hierarchy: **dongle, then coder, then log**. A thread holding the log mutex never asks for another lock, so no cycle between mutexes can form.
 
How races are prevented, with examples:
 
- *Two neighbours taking the same dongle*: both must lock the dongle mutex before reading or setting `is_taken`; the loser sleeps in `pthread_cond_wait`, which releases the mutex and sleeps atomically, and re-checks its condition in a `while` loop when it wakes.
- *Monitor reading a coder's data while the coder updates it*: both sides use the coder's mutex and copy the values to local variables inside the lock.
- *Printing after the end*: the check of `stop` and the `printf` happen under `log_lock`; the monitor changes `stop` under the same lock.
- *Coder to monitor*: coders publish progress only through the mutex-protected fields. *Monitor to coders*: the only channel is the `stop` flag plus the condition-variable broadcasts.
## Testing
 
Checked with valgrind (memcheck and helgrind), and with repeated runs counting compiles and burnouts, for 1 to 201 coders and both schedulers. The heap has an isolated test in `tests/test_heap.c`.
 
Known limitation, measured: with `./codexion 5 800 200 200 200 3 0 fifo`, 2 to 4 runs out of 100 ended in a burnout; with `time_to_burnout` of 850 or 900 there were 0 in 100 runs. The cause is the start-up: the five coders request their first dongle at the same instant, and with the global acquisition order four of them can end up holding one dongle each and compiling one after the other (about 4 x 200 ms), which leaves the last coder past its deadline. Avoiding it entirely would require taking both dongles atomically, which this implementation does not do. A staggered start was tried and gave no measurable improvement, so it was removed.
 
## Resources
 
- `man 3 pthread_create`, `pthread_mutex_lock`, `pthread_cond_wait`, `pthread_cond_timedwait`, `gettimeofday`.
- E. W. Dijkstra, *Hierarchical ordering of sequential processes* (dining philosophers).
- E. G. Coffman, M. J. Elphick, A. Shoshani, *System Deadlocks* (1971).
- C. L. Liu, J. W. Layland, *Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment* (1973), for earliest deadline first.
- T. H. Cormen et al., *Introduction to Algorithms*, chapter on heapsort and priority queues.
- Valgrind manual (Memcheck and Helgrind).
### Use of AI
 
Claude was used as a tutor throughout the project: to explain concepts (threads, mutexes, condition variables, deadlock, heaps), to review code and Norm compliance, and to interpret helgrind/valgrind output and test results.
