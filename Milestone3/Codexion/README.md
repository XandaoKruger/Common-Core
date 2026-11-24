*This project has been created as part of the 42 curriculum by acano-kr.*
 
# Codexion
 
## Description
 
Codexion is a concurrency simulation written in C with POSIX threads. `N` coders sit in a circle, and between every two neighbours there is one USB dongle. Each coder repeats the same cycle:
 
1. **compile**: needs *both* adjacent dongles,
2. **debug**,
3. **refactor**.
A coder suffers **burnout** if `time_to_burnout` ms pass without *starting* a compile (counted from the start of the previous compile, or from the start of the simulation). After a dongle is released it cannot be taken again for `dongle_cooldown` ms. The simulation ends when every coder has compiled `number_of_compiles_required` times, or when the first burnout happens.
 
The goal is to share the dongles without deadlock, to keep coders from being kept waiting for no reason, to detect a burnout with a precision of a few milliseconds, and to keep the log readable. Waiting requests are ordered by a priority queue implemented from scratch (a binary min-heap), under one of two schedulers:
 
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
make norm                                       # norminette on src/ and include/
make val ARGS="5 3000 200 200 200 3 100 edf"    # valgrind (leaks)
make hel ARGS="5 3000 200 200 200 3 100 edf"    # valgrind --tool=helgrind
```
 
Use generous timings under valgrind: it slows the program down a lot, and tight burnouts then fail for reasons unrelated to the logic.
 
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
| `dongle.c` | `take_both` and `release_both`: taking and releasing both dongles at once |
| `dongle_queue.c` | per-dongle request queues and the rule that decides who may start |
| `heap.c`, `heap_utils.c` | binary min-heap used as priority queue |
| `monitor.c`, `monitor_utils.c` | burnout detection, end of simulation, waking sleepers |
| `launch.c` | thread creation and joining |
 
Coder `i` uses dongle `i` and dongle `(i + 1) % N`. Everything shared lives in a single `t_sim` structure that is passed to the threads: there are no global variables.
 
### How a coder gets its dongles
 
A coder never holds one dongle while waiting for the other. It takes **both or none**, in one step done under a single mutex (the "table"):
 
1. It enqueues one request in the queue of each of its two dongles. The key is an arrival counter (FIFO) or `last_compile_start + time_to_burnout` (EDF); ties are broken by the coder id.
2. It may start only when both dongles are free and past their cooldown, **and**, for each of its dongles, either its request is at the top of that dongle's queue, or the coder at the top could not start right now (one of its dongles is busy or cooling down). A coder with lower priority can therefore use dongles that would otherwise stay idle, but it never overtakes a higher-priority neighbour that is ready to start.
3. When it starts, it removes its requests from both queues, marks both dongles as taken and prints the two `has taken a dongle` lines.
4. When it finishes compiling, it marks both dongles as free with `available_at = now + dongle_cooldown` and wakes everybody.
## Blocking cases handled
 
### Deadlock prevention (Coffman's conditions)
 
A deadlock needs four conditions at once: mutual exclusion, hold and wait, no preemption and circular wait.
 
- *Mutual exclusion* and *no preemption* are inherent to the problem (a dongle is used by one coder at a time, until it finishes compiling).
- *Hold and wait* is **removed**: a coder takes both dongles atomically or none, so no coder ever waits for a dongle while holding another one.
- Since nobody waits while holding a resource, a *circular wait* cannot form either.
An earlier version of this project took the dongle with the lowest index first and then waited for the other one (breaking circular wait only). Logs showed coders holding a dongle idle for 600 to 1200 ms while neighbours cooled down, which made some configurations with a large cooldown burn out in about 40% of the runs; the all-or-nothing rule removed that.
 
### Priority and starvation
 
Every dongle has its own queue of pending requests (a min-heap). The rule above makes the order of service follow the scheduler (arrival order for FIFO, nearest deadline for EDF) among the coders that can actually run, and it does not leave dongles idle behind a coder that cannot run. This is a priority rule, not a formal guarantee against starvation; it was validated by measurement (see Testing).
 
### Cooldown handling
 
When a dongle is released, `available_at = now + dongle_cooldown` is stored under the table mutex. If both dongles of a waiting coder are free but still cooling down, the coder releases the mutex, sleeps 0.5 ms, takes the mutex again and re-evaluates; in every other case it waits on the table's condition variable. A release or a stop wakes everybody with a broadcast and each waiter re-checks its condition in a `while` loop.
 
### Precise burnout detection
 
A dedicated monitor thread wakes up every millisecond, and for each coder reads `last_compile_start` and `compile_count` under the coder's mutex. If `now - last_compile_start >= time_to_burnout` and the coder has not finished its compiles, the burnout is declared. In 10 runs of `./codexion 5 500 200 200 200 10 0 fifo`, `burned out` was printed 0 to 4 ms after the deadline and was always the last line (limit in the subject: 10 ms). Coders that already compiled `number_of_compiles_required` times are ignored.
 
### Log serialization
 
All output goes through one function guarded by `log_lock`. The timestamp is computed **inside** the lock, so lines come out in timestamp order and never interleave. The `stop` flag is protected by the same mutex: the monitor sets it and prints `burned out` in the same critical section, so no message can appear after the burnout.
 
### Lost wake-ups and clean termination
 
When the simulation stops, coders may be asleep on the table's condition variable. The monitor sets `stop`, then locks the table mutex, broadcasts and unlocks. Locking before the broadcast matters: a coder checks `stop` while holding the table mutex and only releases it by entering the wait, so it either sees `stop = 1` or is already asleep when the broadcast arrives. `ms_sleep` sleeps in slices of 0.5 ms and checks `stop` on each slice, so coders asleep in a phase also leave quickly. All threads are joined before any memory is freed.
 
### Single coder
 
With one coder, left and right are the same dongle, so the coder can never hold two dongles. It waits, and the monitor reports its burnout at `time_to_burnout`.
 
## Thread synchronization mechanisms
 
| primitive | where | protects |
|---|---|---|
| `pthread_mutex_t table_lock` | `t_sim` | `is_taken`, `available_at`, `arrivals` and the request heap of every dongle |
| `pthread_cond_t table_cond` | `t_sim` | waiting coders: broadcast on every release and on stop |
| `pthread_mutex_t lock` (one per coder) | `t_coder` | `last_compile_start`, `compile_count` (written by the coder, read by the monitor and by the EDF key) |
| `pthread_mutex_t log_lock` | `t_sim` | `stdout` output and the `stop` flag |
 
Lock hierarchy: **table, then coder, then log**. A thread holding the log mutex never asks for another lock, so no cycle between mutexes can form.
 
How races are prevented, with examples:
 
- *Two neighbours taking the same dongle*: the check "both free, cooled down, my turn" and the marking of both dongles as taken happen under the same table mutex, so two coders cannot both succeed. The loser sleeps in `pthread_cond_wait`, which releases the mutex and sleeps atomically, and re-checks its condition in a `while` loop when it wakes.
- *Monitor reading a coder's data while the coder updates it*: both sides use the coder's mutex and copy the values to local variables inside the lock.
- *Printing after the end*: the check of `stop` and the `printf` happen under `log_lock`; the monitor changes `stop` under the same lock.
- *Coder to monitor*: coders publish progress only through the mutex-protected fields. *Monitor to coders*: the only channel is the `stop` flag plus the broadcast on the table's condition variable.
## Testing
 
Checked with valgrind (memcheck, helgrind and drd), repeated runs counting compiles and burnouts, and an isolated test of the heap (`tests/test_heap.c`). Results on this implementation:
 
- `./codexion 5 800 200 200 200 10 0 fifo`, `5 2000 ... 10 0 fifo`, `5 2000 ... 7 0 edf`, `5 3000 ... 10 400 fifo` and `5 3000 ... 10 400 edf`: 20 runs each, no burnout in any of them.
- From 1 to 201 coders with `time_to_burnout` 3000 and a cooldown of 100: every coder completes its compiles, no burnout.
- `5 500 200 200 200 10 0 fifo` always ends with a single `burned out` line, the last one, around timestamp 500.
- With one coder, the burnout is reported at `time_to_burnout`.
## Resources
 
- `man 3 pthread_create`, `pthread_mutex_lock`, `pthread_cond_wait`, `usleep`, `gettimeofday`.
- E. W. Dijkstra, *Hierarchical ordering of sequential processes* (dining philosophers).
- E. G. Coffman, M. J. Elphick, A. Shoshani, *System Deadlocks* (1971).
- C. L. Liu, J. W. Layland, *Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment* (1973), for earliest deadline first.
- T. H. Cormen et al., *Introduction to Algorithms*, chapter on heapsort and priority queues.
- Valgrind manual (Memcheck, Helgrind and DRD).
### Use of AI
 
Claude was used as a tutor throughout the project: to explain concepts (threads, mutexes, condition variables, deadlock, heaps), to review code and Norm compliance, and to interpret valgrind/helgrind/drd output and test results.