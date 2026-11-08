/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_ctx *ctx)
{
	int	x;
	int	y;
	int	z;

	x = ctx->a.val[ctx->a.top];
	y = ctx->a.val[(ctx->a.top + 1) % ctx->a.cap];
	z = ctx->a.val[(ctx->a.top + 2) % ctx->a.cap];
	if (x > y && y < z && x < z)
		sa(ctx);
	else if (x > y && y > z)
	{
		sa(ctx);
		rra(ctx);
	}
	else if (x > y && y < z && x > z)
		ra(ctx);
	else if (x < y && y > z && x < z)
	{
		sa(ctx);
		ra(ctx);
	}
	else if (x < y && y > z && x > z)
		rra(ctx);
}

void	sort_small(t_ctx *ctx)
{
	if (is_sorted(&ctx->a))
		return ;
	if (ctx->a.size == 2)
	{
		sa(ctx);
		return ;
	}
	while (ctx->a.size > 3)
	{
		bring_to_top_a(ctx, find_min_pos(&ctx->a));
		pb(ctx);
	}
	sort_three(ctx);
	while (ctx->b.size > 0)
		pa(ctx);
}
