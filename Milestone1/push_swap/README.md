*This project has been created as part of the 42 curriculum by acano-kr, dserra-d.*

---

# Push_Swap

> *Because Swap_push doesn't feel as natural.*

A sorting algorithm project built in C that sorts a stack of integers using a limited set of operations and the minimum possible number of moves. The program selects the most efficient strategy based on the measured disorder of the input.

---

## Authors

| GitHub |
|--------|
| [![GitHub](https://img.shields.io/badge/GitHub-acano--kr-181717?logo=github&logoColor=white)](https://github.com/XandaoKruger) |
| [![GitHub](https://img.shields.io/badge/GitHub-dserra--d-181717?logo=github&logoColor=white)](https://github.com/Davidtexas-94) |

---

## Description

**Push_swap** receives a list of integers as arguments and outputs the shortest possible sequence of stack operations that sorts them in ascending order.

The program uses two stacks — `a` and `b` — and a set of 11 operations to manipulate them. It implements four distinct sorting strategies and selects the most appropriate one based on a **disorder metric** calculated before any moves are made.

### Available operations

| Operation | Description |
|-----------|-------------|
| `sa` / `sb` / `ss` | Swap the top two elements of stack a / b / both |
| `pa` / `pb` | Push the top element from b to a / from a to b |
| `ra` / `rb` / `rr` | Rotate stack a / b / both upward |
| `rra` / `rrb` / `rrr` | Reverse rotate stack a / b / both |

---

## Instructions

### Requirements

- GCC or Clang with C99 support
- GNU Make
- A Unix-based system (Linux or macOS)

### Compilation

```bash
# Clone the repository
git clone https://github.com/Davidtexas-94/push_swap.git
cd push_swap

# Compile
make

# Clean object files
make clean

# Full clean (including binary)
make fclean

# Recompile from scratch
make re
```

### Usage

```bash
# Basic usage — default strategy (adaptive)
./push_swap 4 67 3 87 23

# Force a specific strategy
./push_swap --simple   5 4 3 2 1
./push_swap --medium   5 4 3 2 1
./push_swap --complex  5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# Enable benchmark mode (outputs metrics to stderr)
./push_swap --bench --adaptive 4 67 3 87 23

# Count total operations generated
./push_swap 4 67 3 87 23 | wc -l

# Verify correctness with checker
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG
```

### Input formats accepted

```bash
# Space-separated arguments
./push_swap 3 1 2

# Quoted string
./push_swap "3 1 2"

# Mixed
./push_swap "3 1" 2 "4 5"
```

### Error handling

The program prints `Error` to stderr and exits in the following cases:

- Non-integer arguments
- Integers outside the valid `int` range
- Duplicate values
- Invalid flags

```bash
./push_swap 0 one 2       # Error
./push_swap 3 2 3         # Error
./push_swap --invalido 1  # Error
```

### Benchmark mode output

When `--bench` is passed, the following is printed to stderr after sorting:

```
[bench] disorder:    XX.XX%
[bench] strategy:    Adaptive / O(n log n)
[bench] total_ops:   XXXX
[bench] sa: X  sb: X  ss: X  pa: X  pb: X
[bench] ra: X  rb: X  rr: X  rra: X  rrb: X  rrr: X
```

---

## Performance Benchmarks

| Input size | Pass (min) | Good | Excellent |
|------------|-----------|------|-----------|
| 100 numbers | < 2000 ops | < 1500 ops | < 700 ops |
| 500 numbers | < 12000 ops | < 8000 ops | < 5500 ops |

```bash
# Test with random input
shuf -i 0-9999 -n 100 > args.txt && ./push_swap $(cat args.txt) | wc -l
shuf -i 0-9999 -n 500 > args.txt && ./push_swap $(cat args.txt) | wc -l
```

---

## Algorithms

### Disorder Metric

Before any sorting begins, the program computes a disorder value between `0.0` and `1.0` using the **Kendall tau distance**: it counts all inversions (pairs where a larger value appears before a smaller one in the stack) and divides by the total number of pairs. A fully sorted stack yields `0.0`; a fully reversed stack yields `1.0`.

```
disorder = inversions / total_pairs
         = inversions / (n * (n - 1) / 2)
```

This metric is computed in O(n²) before any moves are made and is used exclusively by the adaptive strategy to decide which algorithm to apply.

---

### Strategies

| Flag | Algorithm | Complexity | Disorder threshold |
|------|-----------|-----------|-------------------|
| `--simple` | Selection sort variant | O(n²) | < 0.2 |
| `--medium` | Chunk-based sort | O(n√n) | 0.2 – 0.5 |
| `--complex` | Radix sort | O(n log n) | ≥ 0.5 |
| `--adaptive` | Selects above automatically | — | automatic |

---

### `--simple` — Selection Sort (O(n²))

Designed for small or nearly-sorted inputs. For stacks of 2 or 3 elements, it applies a hardcoded sequence of optimal moves derived by exhaustive case analysis. For larger inputs:

1. Find the smallest remaining element in stack `a` using `ra` or `rra` (whichever is shorter).
2. Push it to stack `b` with `pb`.
3. Repeat until `a` is empty.
4. Push everything back to `a` with `pa` — since elements were pushed smallest-first into `b`, they arrive back in sorted order.

This is effectively an O(n²) selection sort: finding and moving each minimum takes up to O(n) rotations, repeated n times.

---

### `--medium` — Chunk Sort (O(n√n))

A divide-and-conquer approach that groups elements by index ranges (chunks) and processes them batch by batch.

1. Assign a normalized index (0 to n-1) to each element based on relative rank.
2. Compute chunk size as `√n + √n/2`, giving approximately `√n` total chunks.
3. For each chunk, scan stack `a` and push all elements whose index falls within `[min, max)` to stack `b`, rotating `a` in the cheaper direction (front or back) to reach each target.
4. Once all elements are in `b`, repeatedly bring the largest remaining index to the top of `b` and push it back to `a`.

The result is a sorted stack `a`. Chunk size is tuned to balance the cost of scanning vs. the number of rounds.

---

### `--complex` — Radix Sort (O(n log n))

A bitwise radix sort operating on the normalized indices of the elements.

1. Assign a normalized index (0 to n-1) to each element, replacing values with their rank.
2. Determine the number of bits needed to represent the largest index: `bits = ⌊log₂(n-1)⌋ + 1`.
3. For each bit position (from least significant to most significant):
   - Iterate through all elements of stack `a`.
   - If the current bit of the element's index is `1`, rotate it to the bottom with `ra`.
   - If the bit is `0`, push it to stack `b` with `pb`.
   - After processing all elements, push everything back from `b` to `a` with `pa`.
4. After all bit passes, stack `a` is sorted.

Each of the `log₂(n)` passes costs O(n) operations, yielding O(n log n) total.

---

### `--adaptive` — Automatic Strategy Selection

Runs `calculate_disorder` on the input and delegates to one of the three strategies above:

- Stack of 3 or fewer → `--simple` unconditionally
- Disorder < 0.2 → `--simple` (input is nearly sorted; a few swaps suffice)
- 0.2 ≤ disorder < 0.5 → `--medium`
- Disorder ≥ 0.5 → `--complex`

This avoids using an expensive O(n log n) algorithm on an input that's already 90% sorted.

---

## Project Structure

```
push_swap/
├── push_swap.h
├── Makefile
├── algorithm/
│   ├── algo_simple.c           # sort_two, sort_three, sort_simple
│   ├── algo_medium.c           # chunk-based sort
│   ├── algo_complex.c          # radix sort
│   ├── algo_utils.c            # disorder metric, index assignment, smallest finder
│   └── algo_utils2.c           # biggest index, chunk position, move helpers
├── operations/
│   ├── operation_utils.c       # swap, rotate, reverse primitives
│   ├── push_swap_operations.c  # sa, sb, ss, pa, pb
│   ├── rotate_operations.c     # ra, rb, rr
│   └── reverse_operations.c    # rra, rrb, rrr
├── srcs/
│   ├── main.c
│   ├── flags.c                 # flag parsing, strategy dispatch
│   ├── parse.c                 # input validation and int parsing
│   ├── stack.c                 # stack init, node creation, free
│   ├── utils.c                 # ft_atol, is_sorted, ft_free_args
│   ├── bench.c                 # benchmark output
│   └── push_swap.c             # init_program, setup_stacks, error
└── libft/                      # Custom C standard library
```

---

## Resources

### References

- [Push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer) — visual debugger for stack operations
- [Sorting Algorithms — Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Kendall tau distance](https://en.wikipedia.org/wiki/Kendall_tau_distance) — basis for the disorder metric
- [Big-O Notation — CS50](https://cs50.harvard.edu/x/2024/notes/3/) — algorithmic complexity reference

### AI Usage

Throughout this project, AI was used as a collaborative tool for:

- **Architecture decisions** — discussing data structure choices (linked list vs array) and their trade-offs for this specific problem
- **Debugging** — identifying logic errors in pointer manipulation and stack operations
- **Code review** — validating correctness of individual functions before integration
- **Understanding complexity** — clarifying how Big-O applies specifically to the push_swap operation model (not classical array operations)

All AI-generated suggestions were reviewed, tested, and fully understood by both authors before being incorporated. No code was blindly copied — every function was written and validated by the team.
