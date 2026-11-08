*This project has been created as part of the 42 curriculum by haait-ba, sael-mgh.*

# push_swap

> *Because Swap_push doesn't feel as natural.*

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-push__swap-000000?style=for-the-badge&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-OK-00BABC?style=for-the-badge)
![Team](https://img.shields.io/badge/Team-2%20learners-00BABC?style=for-the-badge)

---

## 📖 Description

**push_swap** is an algorithm project from the 42 curriculum, done by a team of two.

We have two stacks, `a` and `b`. At the start, `a` holds a list of distinct integers
(negative and/or positive) and `b` is empty. The program must print on the standard
output **the shortest possible sequence of operations** that sorts `a` in ascending
order (smallest on top), using only these operations:

| Operation | Effect |
|:---:|---|
| `sa` / `sb` / `ss` | Swap the first 2 elements of `a` / `b` / both |
| `pa` / `pb` | Take the top of `b` and put it on `a` / the opposite |
| `ra` / `rb` / `rr` | Rotate up (the first element becomes the last) on `a` / `b` / both |
| `rra` / `rrb` / `rrr` | Rotate down (the last element becomes the first) on `a` / `b` / both |

The binary embeds **four sorting strategies**, selected at runtime:

| Flag | Strategy | Complexity (in number of operations) |
|---|---|:---:|
| `--simple` | Min extraction (selection sort adaptation) | O(n²) |
| `--medium` | Chunk-based "butterfly" sort (window ≈ 1.5·√n) | O(n√n) |
| `--complex` | MSD radix sort in base 3, on both stacks | O(n log n) |
| `--adaptive` *(default)* | Picks a method from the measured **disorder** | depends on the regime |

All complexities in this README are measured in **number of push_swap operations
generated**, as required by the subject, not in classic array-sort time.

### Main features

- Arguments as separate numbers (`3 2 1`) or in one string (`"3 2 1"`), or both mixed.
- Errors (`Error\n` on stderr): non-integers, values outside `INT_MIN`…`INT_MAX`,
  duplicates, empty arguments, unknown flags, two strategy flags at once.
- **Disorder metric** computed before any move.
- **`--bench` mode** (on stderr): disorder in % with two decimals, strategy name and
  complexity class, total operations and the count of each of the 11 operations.
- **Bonus:** a `checker` program that checks whether a list of operations sorts the stack.

---

## ⚙️ Instructions

### Compilation

```bash
make          # builds libft, then push_swap
make bonus    # builds checker
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # rebuilds everything
```

Compiled with `cc -Wall -Wextra -Werror`. The only external functions used are
`read`, `write`, `malloc`, `free` and `exit`, plus our own `libft`.

### Usage

```bash
./push_swap 2 1 3 6 5 8                     # adaptive strategy (default)
./push_swap --simple 5 4 3 2 1              # force O(n²)
./push_swap --medium 4 67 3 87 23           # force O(n√n)
./push_swap --complex 4 67 3 87 23          # force O(n log n)
./push_swap "3 2 1" 5 4                     # numbers inside a string also work

ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l                 # count operations
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG        # check with our checker
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG  # check with 42's checker

./push_swap --bench $ARG 2> bench.txt > /dev/null            # metrics only
```

Example of `--bench` output:

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
$> ./push_swap 0 one 2 3
Error
$> ./push_swap 3 2 3
Error
$> ./push_swap 2147483648
Error
$> ./push_swap
$>
```

### Bonus: `checker`

```bash
$> ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK                       # (end the input with Ctrl+D)
$> echo sa | ./checker 1 2 3
KO
$> echo xx | ./checker 1 2
Error
```

---

## 🧠 Algorithms

### Preprocessing

**Indexing** (`08_index.c`): each value is replaced by its rank `0 … n-1`.
`-50 900 3` becomes `0 2 1`. The order stays the same, so the disorder does not
change, but the algorithms can then compare indexes directly ("index ≤ i", "index
in the last third"…). Cost: O(n²) comparisons, O(n) extra memory, **0 operations**.

**Disorder metric** (`09_disorder.c`): the proportion of pairs `(i, j)` with `i < j`
and `a[i] > a[j]` among all `n(n-1)/2` pairs. `0` means already sorted, `1` means sorted
in reverse. It is computed **before any move** and stored × 10000 as an integer
(`40.00%` → `4000`) to avoid floating-point numbers.

**Stack structure** (`01_stack.c`): each stack is a **circular buffer** (an array of
`n` ints plus a `top` index). `push`, `swap`, `rotate` and `reverse_rotate` are all
O(1): a rotation only moves `top` by one cell instead of shifting the whole array.

### 0. Small inputs (n ≤ 5) — `11_sort_small.c`

- 2 numbers: one `sa` if needed.
- 3 numbers: each of the 6 possible orders is handled by a fixed case, with
  **at most 2 operations**.
- 4–5 numbers: push the minimum to `b` (bringing it to the top the shortest way)
  until 3 remain, sort the 3, then `pa` everything back. At most 6 operations for 4
  numbers and 10 for 5 (checked on all permutations).

### 1. Simple — O(n²) — `12_sort_simple.c`

**Principle (min extraction):** while `a` is not sorted, bring the minimum of `a` to the
top (with `ra` if it is in the top half, `rra` otherwise), then `pb`. At the end, `pa`
everything back: `b` holds the numbers in descending order, so `a` ends up sorted.
The loop stops early as soon as what remains in `a` is already sorted.

**Bound:** each extraction costs at most `size/2` rotations + 1 push.
Sum over the `n` extractions ≤ n²/4 + 2n → **O(n²)** operations.
Memory: O(1) besides the stacks.

### 2. Medium — O(n√n) — `13_sort_medium.c`

**Push to `b` ("butterfly"):** a counter `i` starts at 0, and a window of width
`r ≈ 1.5·√n` (15 for 100 numbers, 33 for 500). For the top value `v` of `a`:
- `v ≤ i` → `pb` then `rb` (small values go to the bottom of `b`), `i++`;
- `v ≤ i + r` → `pb` (stays on top of `b`), `i++`;
- otherwise → `ra`.

`b` ends up almost sorted, with the biggest values near the top and the smallest
near the bottom (the shape of a butterfly's wings).

**`rr` optimisation:** after a `pb` of a small value, the `rb` is not printed right away.
If the next move is an `ra`, both are printed together as one `rr` (`pb rb ra` → `pb rr`).
This is safe because `ra` only touches `a`.

**Push back to `a`:** `b` holds exactly the indexes `0 … b.size-1`, so the maximum is
always `b.size-1`. We compare the cost of bringing the maximum and the second maximum
to the top. If the second one is cheaper, we push it first, then the maximum, then `sa`.

**Bound:** a value is rotated while it is outside the window, so `a` is turned at most
O(n / r) times, each turn costing O(n) → O(n² / r) = O(n√n). When pushing back, each value
is at most O(r) positions away from the top of `b` → O(n·r) = O(n√n).
Memory: O(1) besides the stacks.

### 3. Complex — MSD radix sort in base 3 — O(n log n) — `14_sort_complex.c`, `14_complex_utils.c`

**Principle:** a **most-significant-digit (MSD) radix sort**, in **base 3**, on the
indexes `0 … n-1`. A range `[lo, lo+len)` is split by its most significant base-3 digit:

```
digit = (v - lo) * 3 / len        → 0, 1 or 2
d1 = lo + len/3,  d2 = lo + 2·len/3   (limits between the digits)
```

- **`radix_a`** (range on top of `a`), one bucketing pass `bucket_a`:
  digit 2 → stays in `a` (`ra`), digit 1 → bottom of `b` (`pb` then `rb`),
  digit 0 → top of `b` (`pb`). Then the rotations are undone (with `rrr` while both
  stacks need it), bucket 2 is sorted in `a`, and buckets 1 and 0 are sorted from `b`.
- **`radix_b`** (range on top of `b`), pass `bucket_b`: digit 2 → top of `a` (`pa`),
  digit 1 → bottom of `a` (`pa` then `ra`), digit 0 → stays in `b` (`rb`).
  Then bucket 2 is sorted, bucket 1 is brought back, and bucket 0 is sorted.
- Each bucket is sorted again on its **next** digit (recursion), until it holds 3 values
  or fewer, or is already sorted (then it is finished directly).
- A pending `rb` (or `ra`) followed by an `ra` (or `rb`) is merged into one `rr`.

**Why MSD and not the classic LSD (binary) radix:** an LSD binary radix needs
`log₂(n)` passes, and **every** value moves at least once per pass: for 100 numbers
that is 7 passes × 100 = **at least 700 operations**, plus the `pa` to bring them back
(our first version made 1084). LSD also needs every pass to keep the order of the
previous one (stability), so passes cannot be shortened. With MSD, each finished bucket
is never touched again, and the buckets get smaller at each level.

**Why base 3:** in one move a value can be dropped in **3 places** (stay in `a`, top of
`b`, bottom of `b`), so 3 buckets per pass cost nothing extra. Ranges are divided by 3
at each level instead of 2, which means fewer levels and fewer operations.

**Bound:** at each digit level, each value gets O(1) operations (one push or one
rotation, plus at most one reverse rotation). The ranges are divided by 3 at each
level, so there are log₃(n) levels → **O(n log n)** operations.
Memory: O(1) besides the stacks, plus O(log n) for the recursion.

### 4. Adaptive — `16_sort_adaptive.c` (default)

| Condition | Regime | Method used | Complexity |
|:---:|---|---|:---:|
| `n ≤ 5` | tiny | small sort | O(1) (≤ 10 ops) |
| `disorder < 0.2` | low | simple (min extraction) | O(n²) |
| `0.2 ≤ disorder < 0.5` | medium | medium (butterfly chunks) | O(n√n) |
| `disorder ≥ 0.5` | high | complex (MSD radix, base 3) | O(n log n) |

**Why these thresholds:** `0.2` and `0.5` are the regime limits given by the subject
(`LOW_DISORDER` and `HIGH_DISORDER` in `push_swap.h`). Each regime uses the strategy
whose complexity class matches the target of that regime.

- **Low disorder (< 0.2):** most pairs are already in order. Min extraction is the
  simplest method, it stops as soon as the rest of `a` is sorted, and its upper bound
  is O(n²), as required.
- **Medium disorder (0.2 – 0.5):** the input is still partly ordered. The butterfly
  chunk sort gets the lowest counts in this range (see the measurements below), and
  it is O(n√n).
- **High disorder (≥ 0.5):** the input is close to random or reversed. This is where
  the base-3 MSD radix sort is best for big inputs, with O(n log n) operations.

**Time and space of the selection itself:** the disorder is computed once in O(n²)
comparisons (0 operations), and the choice is O(1). Total memory stays O(n) (the two
stacks), plus O(log n) recursion in the high regime.

---

## 📊 Performance

Averages over 40 random inputs (all outputs checked as sorted):

| Strategy | 100 numbers (avg / max) | 500 numbers (avg / max) |
|---|:---:|:---:|
| `--simple` | 1405 / 1609 | 32212 / 33739 |
| `--medium` | 535 / 567 | 4605 / 4752 |
| `--complex` | 657 / 681 | 4243 / 4295 |
| `--adaptive` (default) | **606 / 669** | **4405 / 4705** |

Subject targets: 100 numbers < 700 (excellent), 500 numbers < 5500 (excellent).
The default mode reaches the "excellent" level for both sizes.

Partly sorted inputs (one example each):

| n | disorder | simple | medium | complex | adaptive picks |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 100 | 5.77% | 260 | 230 | 566 | simple → 260 |
| 100 | 25.53% | 852 | 410 | 650 | medium → 410 |
| 500 | 12.68% | 8705 | 2229 | 4205 | simple → 8705 |
| 500 | 21.95% | 16939 | 3107 | 4263 | medium → 3107 |

---

## 👥 Contributions

The subject requires that **both learners contribute meaningfully and understand all
the code**. Each one owned her part, and every part was reviewed and explained to the
other before being merged (pull request + cross review).

### 🟦 Hanane — `haait-ba`

**Foundations: stacks, operations, parsing — simple and medium algorithms**

- `Makefile` (`$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`, no relink) with `libft`
- Stack structure (circular buffer) and memory freeing
- The 11 operations (`sa` … `rrr`), with output and counters for the bench
- Argument parsing: separate numbers or numbers in one string (`"3 2 1"`)
- Error handling → `Error\n` on stderr
- **Simple strategy — O(n²)** (`--simple`)
- **Medium strategy — O(n√n)** (`--medium`)
- `--bench` mode

### 🟪 Sanae — `sael-mgh`

**Foundations: input analysis — complex and adaptive algorithms**

- Flag parsing (`--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`)
- Value indexing (each number replaced by its rank `0 … n-1`)
- **Disorder** computation (`compute_disorder`) before any move
- Special sorts for small sizes (2, 3 and 5 elements)
- **Complex strategy — O(n log n)** (`--complex`)
- **Adaptive strategy** (`--adaptive`, default)

### 🤝 Together

- **Bonus:** `checker` program
- Optimisations (merging `ra` + `rb` → `rr`, `rra` + `rrb` → `rrr`)
- Choice and justification of the adaptive thresholds
- Tests: errors, edge cases, 100 / 500 random numbers, `checker_linux`
- `norminette` and memory leak checks
- This README
- Defense preparation: each of us can explain **all** the code

### Git workflow

- `main`: stable version, always compiles
- One branch per task: `hanane/parsing`, `sanae/radix`, …
- Merge into `main` only through a pull request reviewed by the other

---

## 🗂️ Project structure

The Norm allows at most 5 functions per file and 25 lines per function, so the code
is split into small files, numbered in the order they were written.

```
push_swap/
├── Makefile                  ← builds libft, then push_swap / checker        (Hanane)
├── README.md
├── includes/
│   ├── push_swap.h           ← structures, enums and prototypes              (together)
│   └── checker_bonus.h       ← prototypes of the checker                     (together)
├── libft/                    ← our libft (sources + Makefile)
├── srcs/
│   ├── 00_main.c             ← parsing → index → disorder → sort → bench     (Sanae)
│   ├── 01_stack.c            ← init / free the stacks, error_exit            (Hanane)
│   ├── 02_parsing.c          ← argv → numbers                                (Hanane)
│   ├── 03_parsing_utils.c    ← atoi with overflow check, duplicates          (Hanane)
│   ├── 04_ops_swap.c         ← sa  sb  ss                                    (Hanane)
│   ├── 05_ops_push.c         ← pa  pb                                        (Hanane)
│   ├── 06_ops_rotate.c       ← ra  rb  rr                                    (Hanane)
│   ├── 07_ops_rev_rotate.c   ← rra rrb rrr                                   (Hanane)
│   ├── 08_index.c            ← values → ranks 0 … n-1                        (Sanae)
│   ├── 09_disorder.c         ← disorder metric, is_sorted                    (Sanae)
│   ├── 10_sort_utils.c       ← min / max, bring to top, rotate_both (rr/rrr) (together)
│   ├── 11_sort_small.c       ← sorts for 2, 3 and 5 elements                 (Sanae)
│   ├── 12_sort_simple.c      ← --simple    O(n²)                             (Hanane)
│   ├── 13_sort_medium.c      ← --medium    O(n√n)                            (Hanane)
│   ├── 14_sort_complex.c     ← --complex   O(n log n)                        (Sanae)
│   ├── 14_complex_utils.c    ← radix helpers (digit limits, small buckets)   (together)
│   ├── 15_flags.c            ← flag parsing (--simple, --bench…)             (Sanae)
│   ├── 16_sort_adaptive.c    ← --adaptive and strategy dispatch              (Sanae)
│   └── 17_bench.c            ← --bench output on stderr                      (Hanane)
└── bonus/
    ├── checker_bonus.c       ← checker main: parse, read, apply, OK/KO       (together)
    └── checker_utils_bonus.c ← read_line, apply_swap_push, apply_rotate      (together)
```

### How the checker works

1. Parses the arguments with **the same functions** as push_swap.
2. Reads stdin one character at a time with `read` (`read_line`), one operation per
   line, into a 5-cell buffer owned by `main` (no `malloc`, so no leak).
3. Applies each operation with the **silent primitives** (`swap`, `push`, `rotate`,
   `reverse_rotate`), which do the move without printing anything.
4. Unknown or badly formatted operation → `Error` on stderr.
   At the end: `a` sorted **and** `b` empty → `OK`, otherwise `KO`.

---

## 📚 Resources

- [push_swap subject (42 intra)](https://projects.intra.42.fr/projects/42cursus-push_swap)
- [Radix sort (LSD and MSD) — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort)
- [Selection sort — Wikipedia](https://en.wikipedia.org/wiki/Selection_sort)
- [Big O notation — Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation)
- [Inversions (disorder metric) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
- [Circular buffer — Wikipedia](https://en.wikipedia.org/wiki/Circular_buffer)
- [`read(2)` — Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)
- A push_swap visualizer, used to watch the stacks move during our tests

### Use of AI

We used an AI assistant (Claude) as a tutor and a reviewer, not as a replacement for
understanding. Everything it produced was read, tested and explained between the two
of us before being kept.

- **Explanations:** concepts like `read` and file descriptors, circular buffers,
  complexity bounds in the push_swap model, step-by-step traces of our functions,
  and practice for the defense.
- **Complex strategy:** turning our first LSD binary radix (1084 operations for 100
  numbers) into the base-3 MSD radix, to get under 700.
- **Optimisation:** the `rotate_both` helper and the merge of `ra` + `rb` into `rr`
  in the medium sort (`10_sort_utils.c`, `13_sort_medium.c`).
- **Bonus:** help writing the `checker` (`bonus/`), after we drafted it ourselves.
- **Tests and docs:** ideas for edge-case tests, benchmark scripts, and the structure
  and English wording of this README.

The algorithms themselves (strategy choice, chunk and radix bucket logic, thresholds) are our
own design.
