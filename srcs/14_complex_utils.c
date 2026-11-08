/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_complex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:56:59 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 00:56:59 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_part	make_part(int lo, int len, int whole)
{
	t_part	p;

	p.p1 = lo + len / 3;
	p.p2 = lo + 2 * len / 3;
	p.nbig = 0;
	p.nmid = 0;
	p.pushed = 0;
	p.whole = whole;
	p.rot = 0;
	return (p);
}

/* asc = 1: top len ascending (a), asc = 0: top len descending (b) */
int	top_sorted(t_stack *s, int len, int asc)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < len - 1)
	{
		x = s->val[(s->top + i) % s->cap];
		y = s->val[(s->top + i + 1) % s->cap];
		if ((asc && x > y) || (!asc && x < y))
			return (0);
		i++;
	}
	return (1);
}

/* sort the top len (<= 3) of a without touching what is below */
void	sort_top_a(t_ctx *ctx, int len)
{
	while (!top_sorted(&ctx->a, len, 1))
	{
		if (ctx->a.val[ctx->a.top]
			> ctx->a.val[(ctx->a.top + 1) % ctx->a.cap])
			sa(ctx);
		else if (ctx->a.size == 3)
			rra(ctx);
		else
		{
			ra(ctx);
			sa(ctx);
			rra(ctx);
		}
	}
}

/* undo na "ra" on a and nb "rb" on b.
** Negative counts = reverse rotations, so rotate_both prints "rrr"
** while BOTH stacks still need one (1 op instead of rra + rrb),
** then the leftover rra or rrb alone. */
void	unrotate(t_ctx *ctx, int na, int nb)
{
	rotate_both(ctx, -na, -nb);
}

/* move the top len of b to a, ends sorted if len <= 3 */
void	push_back_b(t_ctx *ctx, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		pa(ctx);
	if (len <= 3)
		sort_top_a(ctx, len);
}
