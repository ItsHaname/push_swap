*This project has been created as part of the 42 curriculum by haait-ba, sael-mgh.*

# push_swap

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-push__swap-000000?style=for-the-badge&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-OK-00BABC?style=for-the-badge)

## Description

**push_swap** sorts a list of distinct integers using two stacks, `a` and `b`, and
a fixed set of 11 operations. The program prints the sequence of operations that
sorts `a` in ascending order (smallest on top), and tries to keep that sequence short.

| Operation | Effect |
|:---:|---|
| `sa` / `sb` / `ss` | Swap the first two elements of `a` / `b` / both |
| `pa` / `pb` | Move the top of `b` onto `a` / the top of `a` onto `b` |
| `ra` / `rb` / `rr` | Rotate up (the first element becomes the last) on `a` / `b` / both |
| `rra` / `rrb` / `rrr` | Rotate down (the last element becomes the first) on `a` / `b` / both |

The program contains four strategies, selected with a flag:

| Flag | Strategy | Operations |
|---|---|:---:|
| `--simple` | Min extraction (selection sort) | O(n²) |
| `--medium` | Chunk sort ("butterfly") | O(n√n) |
| `--complex` | LSD binary radix sort | O(n log n) |
| `--adaptive` *(default)* | Chooses one of the above from the input's disorder | depends on input |

Complexities are counted in **push_swap operations printed**, not in CPU time.

### Features

- Numbers as separate arguments (`3 2 1`), in one string (`"3 2 1"`), or both mixed.
- Prints `Error\n` on stderr for: non-integers, values outside the `int` range,
  duplicates, empty arguments, unknown flags, and more than one strategy flag.
- A **disorder metric**, computed before any operation.
- **`--bench`** mode: prints statistics to stderr.
- **Bonus:** a `checker` program that checks whether a list of operations sorts the stack.

## Instructions

### Build

```bash
make          # libft + push_swap
make bonus    # checker
make clean    # remove object files
make fclean   # remove object files and binaries
make re       # full rebuild
```

The project compiles with `cc -Wall -Wextra -Werror`. It uses only `read`, `write`,
`malloc`, `free`, `exit` and our own `libft`.

### Usage

```bash
./push_swap 2 1 3 6 5 8               # adaptive (default)
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap "3 2 1" 5 4               # string and separate arguments mixed

ARG="4 67 3 87 23"
./push_swap $ARG | wc -l              # number of operations
./push_swap $ARG | ./checker $ARG     # verify with our checker
./push_swap $ARG | ./checker_linux $ARG
```

### `--bench`

```
$> ./push_swap --bench 4 67 3 87 23 > /dev/null
[bench] disorder: 40.00%
[bench] strategy: Adaptive / O(n^2)
[bench] total_ops: 9
[bench] sa: 0 sb: 0 ss: 0 pa: 2 pb: 2
[bench] ra: 4 rb: 0 rr: 0 rra: 1 rrb: 0 rrr: 0
```

### Errors

```bash
$> ./push_swap 0 one 2
Error
$> ./push_swap 3 2 3
Error
$> ./push_swap --simple --medium 1 2
Error
$> ./push_swap           # no argument: prints nothing
```

### Bonus: `checker`

```bash
$> ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK                       # end the input with Ctrl+D
$> echo sa | ./checker 1 2 3
KO
$> echo xx | ./checker 1 2
Error
```

## Algorithms

### Preprocessing

- **Stacks** (`01_stack.c`): each stack is a **circular buffer**, an array plus a
  `top` index. `swap`, `push`, `rotate` and `reverse_rotate` are all O(1), because a
  rotation moves `top` instead of shifting the whole array.
- **Indexing** (`08_index.c`): each value is replaced by its rank `0 … n-1`
  (`-50 900 3` becomes `0 2 1`). The relative order does not change, and the
  algorithms can work on small consecutive numbers. Cost: 0 operations.
- **Disorder** (`09_disorder.c`): the number of inverted pairs (`i < j` and
  `a[i] > a[j]`) divided by the number of pairs, `n(n-1)/2`. `0` means sorted and
  `1` means reverse-sorted. It is stored × 10000 as an integer (`40.00%` → `4000`),
  so no floating-point numbers are needed.

### Small inputs (n ≤ 5): `11_sort_small.c`

- 2 numbers: one `sa` if needed.
- 3 numbers: one fixed case per permutation, **at most 2 operations**.
- 4–5 numbers: push the minimum to `b` (by the shorter rotation direction) until
  3 remain, sort those 3, then `pa` back. **At most 10 operations** for 5 numbers.

### Simple: O(n²), `12_sort_simple.c`

While `a` is not sorted: bring the minimum to the top (`ra` or `rra`, whichever is
shorter), then `pb`. Then `pa` everything back. `b` holds the values in descending
order, so `a` ends up sorted. The loop stops early if the rest of `a` is already sorted.

Each extraction costs at most `n/2` rotations + 1 push → **O(n²)**.

### Medium: O(n√n), `13_sort_medium.c`

1. **Push to `b`:** a counter `i` starts at 0, with a window `r ≈ 1.5·√n`.
   For the top value `v` of `a`:
   - `v ≤ i` → `pb` then `rb` (goes to the bottom of `b`), `i++`
   - `v ≤ i + r` → `pb` (stays on top of `b`), `i++`
   - otherwise → `ra`
2. **Push back to `a`:** bring the maximum of `b` to the top by the shorter
   direction, then `pa`. Repeat until `b` is empty.

After step 1, `b` is almost sorted (big values near the top, small near the bottom),
so each maximum is close to one end of `b`. Step 1 costs O(n²/r) and step 2 costs
O(n·r). With `r ≈ √n`, both are **O(n√n)**.

### Complex: O(n log n), `14_sort_complex.c`

**LSD binary radix sort** on the indexes. For each bit, from least to most significant:
send every element of `a` with that bit at `0` to `b` (`pb`), rotate the others (`ra`),
then `pa` everything back. The pass keeps the relative order, so after the last bit
`a` is sorted.

There are `⌈log₂ n⌉` passes and each costs at most `2n` operations, so the total is
**O(n log n)**. The sort stops early if `a` is already sorted after a pass.

### Adaptive (default): `16_sort_adaptive.c`

| Condition | Method | Operations |
|:---:|---|:---:|
| `n ≤ 5` | small sort | ≤ 10 |
| `disorder < 0.2` | simple | O(n²) |
| `0.2 ≤ disorder < 0.5` | medium | O(n√n) |
| `disorder ≥ 0.5` | complex | O(n log n) |

The thresholds `0.2` and `0.5` are the ones given by the subject (`LOW_DISORDER` and
`HIGH_DISORDER` in `push_swap.h`).

- **Low disorder:** the input is almost sorted, so few minimums are far from the top,
  and the loop stops as soon as the rest is sorted.
- **Medium disorder:** chunk sort performs well on partly ordered inputs.
- **High disorder:** radix sort has the best upper bound for random or reversed inputs.

Choosing the strategy costs 0 operations: the disorder is computed once, in O(n²)
comparisons.

## Performance

Measured on 20 random inputs per size. Every output was checked with `checker_linux`.

| Strategy | 100 numbers (avg / max) | 500 numbers (avg / max) |
|---|:---:|:---:|
| `--simple` | 1442 / 1599 | 32045 / 34126 |
| `--medium` | 570 / 599 | 5037 / 5189 |
| `--complex` | 1084 / 1084 | 6784 / 6784 |
| `--adaptive` | 827 / 1084 | 5839 / 6784 |

For random inputs the disorder is close to 50%. Adaptive therefore switches between
medium and complex, which explains the gap between its average and its maximum.

Nearly sorted inputs (disorder < 20%, one example each), where adaptive picks **simple**:

| n | disorder | `--simple` | `--medium` | `--complex` | `--adaptive` |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 100 | 2.28% | 253 | 247 | 1084 | simple → 253 |
| 100 | 15.33% | 704 | 369 | 1084 | simple → 704 |
| 500 | 4.48% | 4088 | 1308 | 6784 | simple → 4088 |
| 500 | 13.69% | 11402 | 2807 | 6784 | simple → 11402 |

## Project structure
<img width="1041" height="822" alt="image" src="https://github.com/user-attachments/assets/5a29817b-59e6-4f64-a4de-09837adb3705" />
<img width="861" height="876" alt="image" src="https://github.com/user-attachments/assets/81d3eff7-2514-416a-b9eb-c1064ea0ac7f" />

```
push_swap/
├── Makefile
├── includes/
│   ├── push_swap.h            structures, constants, prototypes
│   └── checker_bonus.h        checker prototypes
├── libft/
├── srcs/
│   ├── 00_main.c              parse → index → disorder → sort → bench
│   ├── 01_stack.c             stack init / free, error_exit
│   ├── 02_parsing.c           argv → numbers
│   ├── 03_parsing_utils.c     atoi with overflow check, duplicates
│   ├── 04_ops_swap.c          sa sb ss
│   ├── 05_ops_push.c          pa pb
│   ├── 06_ops_rotate.c        ra rb rr
│   ├── 07_ops_rev_rotate.c    rra rrb rrr
│   ├── 08_index.c             values → ranks
│   ├── 09_disorder.c          disorder, is_sorted
│   ├── 10_sort_utils.c        find min / max, bring to top
│   ├── 11_sort_small.c        n ≤ 5
│   ├── 12_sort_simple.c       --simple
│   ├── 13_sort_medium.c       --medium
│   ├── 14_sort_complex.c      --complex
│   ├── 15_flags.c             flag parsing
│   ├── 16_sort_adaptive.c     --adaptive, strategy dispatch
│   └── 17_bench.c             --bench output
└── bonus/
    ├── checker_bonus.c        checker main
    └── checker_utils_bonus.c  read_line, apply_op
```

### How the checker works

1. It parses the arguments with the same functions as `push_swap`.
2. `read_line` reads stdin one character at a time into a 5-byte buffer, one
   operation per line. No `malloc` is needed.
3. `apply_op` applies each operation without printing. It calls `apply_swap_push`
   and then `apply_rotate`, because one function for all 11 operations would break
   the 25-line limit.
4. An unknown operation prints `Error`. At the end it prints `OK` if `a` is sorted
   and `b` is empty, and `KO` otherwise.

## Contributions

### Hanane (`haait-ba`)

- `Makefile` and `libft` integration
- Stack structure (circular buffer)
- The 11 operations and their counters
- Argument parsing and error handling
- Simple and medium strategies
- `--bench` mode

### Sanae (`sael-mgh`)

- Flag parsing
- Indexing and disorder computation
- Small-input sorts
- Complex and adaptive strategies

### Together

- Bonus `checker`
- Tests (errors, edge cases, 100 / 500 numbers, `checker_linux`), norminette, leak checks
- Code review through pull requests, so that each of us can explain all of the code

## Resources

- [Radix sort: Wikipedia](https://en.wikipedia.org/wiki/Radix_sort)
- [Selection sort: Wikipedia](https://en.wikipedia.org/wiki/Selection_sort)
- [Big O notation: Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation)
- [Inversion (discrete mathematics): Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
- [Circular buffer: Wikipedia](https://en.wikipedia.org/wiki/Circular_buffer)
- [`read(2)`: Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)

### Use of AI

We used AI as a design tool to help us build the UML diagrams of the project and to
explain theoretical concepts (algorithm complexity, sorting methods, data structures).
