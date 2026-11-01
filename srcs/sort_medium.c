/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:24:02 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/01 12:24:02 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_size(int n)
{
	int	r;

	r = 1;
	while (r * r < n)
		r++;
	return (r);
}

static void	push_chunks(t_ctx *ctx)
{
	int	size;
	int	limit;

	size = chunk_size(ctx->a.size);
	limit = size;
	while (ctx->a.size > 0)
	{
		if (ctx->a.val[0] < limit)
		{
			pb(ctx);
			if (ctx->b.size == limit)
				limit += size;
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
