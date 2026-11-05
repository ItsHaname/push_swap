/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_ctx *ctx)
{
	int	x;
	int	y;
	int	z;

	x = ctx->a.val[0];
	y = ctx->a.val[1];
	z = ctx->a.val[2];
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
