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
	int	rot;

	i = 0;
	rot = 0;
	range = chunk_range(ctx->a.size);
	while (ctx->a.size > 0)
	{
		v = ctx->a.val[ctx->a.top];
		if (v > i + range)
			rotate_both(ctx, 1, rot);
		else
		{
			rotate_both(ctx, 0, rot);
			pb(ctx);
		}
		rot = (v <= i && ctx->b.size > 1);
		i += (v <= i + range);
	}
	rotate_both(ctx, 0, rot);
}

static int	pos_of(t_stack *s, int v)
{
	int	i;

	i = 0;
	while (i < s->size && s->val[(s->top + i) % s->cap] != v)
		i++;
	return (i);
}

static int	cost(t_stack *s, int pos)
{
	if (pos <= s->size / 2)
		return (pos);
	return (s->size - pos);
}

void	sort_medium(t_ctx *ctx)
{
	int	max;
	int	p_max;
	int	p_sec;

	push_chunks(ctx);
	while (ctx->b.size > 0)
	{
		max = ctx->b.size - 1;
		p_max = pos_of(&ctx->b, max);
		p_sec = pos_of(&ctx->b, max - 1);
		if (ctx->b.size > 1 && cost(&ctx->b, p_sec) < cost(&ctx->b, p_max))
		{
			bring_to_top_b(ctx, p_sec);
			pa(ctx);
			bring_to_top_b(ctx, pos_of(&ctx->b, max));
			pa(ctx);
			sa(ctx);
		}
		else
		{
			bring_to_top_b(ctx, p_max);
			pa(ctx);
		}
	}
}
