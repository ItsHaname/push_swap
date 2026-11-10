/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_complex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:56:59 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/10/31 00:56:59 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_radix	make_radix(int lo, int len, int whole)
{
	t_radix	r;

	r.d1 = lo + len / 3;
	r.d2 = lo + 2 * len / 3;
	r.nbig = 0;
	r.nmid = 0;
	r.pushed = 0;
	r.whole = whole;
	r.rot = 0;
	return (r);
}

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

void	unrotate(t_ctx *ctx, int na, int nb)
{
	rotate_both(ctx, -na, -nb);
}

void	push_back_b(t_ctx *ctx, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		pa(ctx);
	if (len <= 3)
		sort_top_a(ctx, len);
}
