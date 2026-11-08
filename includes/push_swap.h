/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:09:46 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 16:09:46 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

/* ========================= CONSTANTS ========================= */

/* disorder is stored x 10000  (20.00% = 2000, 50.00% = 5000) */
# define LOW_DISORDER	2000
# define HIGH_DISORDER	5000

/* ========================= ENUMS ============================= */

typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_op;

typedef enum e_strat
{
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
	STRAT_ADAPTIVE
}	t_strat;

/* ========================= STRUCTS =========================== */

/* circular buffer: logical element i is val[(top + i) % cap]
** i = 0 is the top of the stack, i = size - 1 is the bottom */
typedef struct s_stack
{
	int		*val;
	int		size;
	int		cap;
	int		top;
}	t_stack;

/* one quicksort partition: pivots p1 < p2 split the range in thirds */
typedef struct s_part
{
	int		p1;
	int		p2;
	int		nbig;
	int		nmid;
	int		pushed;
	int		whole;
	int		rot;
}	t_part;

typedef struct s_ctx
{
	t_stack	a;
	t_stack	b;
	int		total;
	int		counts[OP_COUNT];
	long	disorder;
	t_strat	strategy;
	t_strat	used;
	int		strat_set;
	int		bench;
}	t_ctx;

/* ================= INIT / FREE / ERRORS  (Hanane) ============ */

void	init_ctx(t_ctx *ctx);
void	init_stacks(t_ctx *ctx, int n);
void	free_ctx(t_ctx *ctx);
void	error_exit(t_ctx *ctx);

/* ===================== FLAGS  (Sanae) ======================== */

int		is_flag(char *arg);
void	parse_flags(t_ctx *ctx, int argc, char **argv);

/* ===================== NUMBERS  (Hanane) ===================== */

int		count_numbers(t_ctx *ctx, int argc, char **argv);
void	parse_numbers(t_ctx *ctx, int argc, char **argv);
int		safe_atoi(char *s, int *ok);
int		has_duplicates(t_stack *s);
int		count_words(char *str, char c);
void	free_split(char **tab);

/* ============ PRIMITIVES, NO OUTPUT  (Hanane) ================ */
/* also used by the bonus checker */

void	swap(t_stack *s);
void	push(t_stack *from, t_stack *to);
void	rotate(t_stack *s);
void	reverse_rotate(t_stack *s);

/* ========== OPERATIONS, PRINT + COUNT  (Hanane) ============== */

void	log_op(t_ctx *ctx, t_op op);
void	sa(t_ctx *ctx);
void	sb(t_ctx *ctx);
void	ss(t_ctx *ctx);
void	pa(t_ctx *ctx);
void	pb(t_ctx *ctx);
void	ra(t_ctx *ctx);
void	rb(t_ctx *ctx);
void	rr(t_ctx *ctx);
void	rra(t_ctx *ctx);
void	rrb(t_ctx *ctx);
void	rrr(t_ctx *ctx);

/* ==================== ANALYSIS  (Sanae) ====================== */

void	assign_index(t_ctx *ctx);
long	compute_disorder(t_stack *s);
int		is_sorted(t_stack *s);

/* ================= SHARED HELPERS  (both) ==================== */

int		find_min_pos(t_stack *s);
int		find_max_pos(t_stack *s);
void	bring_to_top_a(t_ctx *ctx, int pos);
void	bring_to_top_b(t_ctx *ctx, int pos);
void	rotate_both(t_ctx *ctx, int na, int nb);

/* ============== QUICKSORT HELPERS (complex) ================= */

t_part	make_part(int lo, int len, int whole);
int		top_sorted(t_stack *s, int len, int asc);
void	sort_top_a(t_ctx *ctx, int len);
void	push_back_b(t_ctx *ctx, int len);
void	unrotate(t_ctx *ctx, int na, int nb);

/* ================== ALGORITHMS =============================== */

void	sort_small(t_ctx *ctx);
void	sort_simple(t_ctx *ctx);
void	sort_medium(t_ctx *ctx);
void	sort_complex(t_ctx *ctx);
void	sort_adaptive(t_ctx *ctx);
void	run_strategy(t_ctx *ctx);

/* ==================== BENCH  (Hanane) ======================== */

void	print_percent(long x);
void	print_bench(t_ctx *ctx);

#endif
