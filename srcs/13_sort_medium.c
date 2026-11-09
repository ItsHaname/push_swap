/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_sort_medium.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:24:02 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/01 12:24:02 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_range(int n)
{
	int	r;

	r = 1;
	while (r * r < n)
		r++;
	return (r * 3 / 2);
}

static void	push_chunks(t_ctx *ctx)
{
	int	i;
	int	range;
	int	v;

	i = 0;
	range = chunk_range(ctx->a.size);
	while (ctx->a.size > 0)
	{
		v = ctx->a.val[ctx->a.top];
		if (v <= i)
		{
			pb(ctx);
			rb(ctx);
			i++;
		}
		else if (v <= i + range)
		{
			pb(ctx);
			i++;
		}
		else
			ra(ctx);
	}
}

void	sort_medium(t_ctx *ctx)
{
	push_chunks(ctx);
	while (ctx->b.size > 0)
	{
		bring_to_top_b(ctx, find_max_pos(&ctx->b));
		pa(ctx);
	}
}
