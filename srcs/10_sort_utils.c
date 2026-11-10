/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:56:59 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 00:56:59 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_pos(t_stack *s)
{
	int	i;
	int	pos;

	if (s->size == 0)
		return (-1);
	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->val[(s->top + i) % s->cap] < s->val[(s->top + pos) % s->cap])
			pos = i;
		i++;
	}
	return (pos);
}

int	find_max_pos(t_stack *s)
{
	int	i;
	int	pos;

	if (s->size == 0)
		return (-1);
	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->val[(s->top + i) % s->cap] > s->val[(s->top + pos) % s->cap])
			pos = i;
		i++;
	}
	return (pos);
}

void	bring_to_top_a(t_ctx *ctx, int pos)
{
	int	n;

	if (pos <= ctx->a.size / 2)
	{
		n = pos;
		while (n > 0)
		{
			ra(ctx);
			n--;
		}
	}
	else
	{
		n = ctx->a.size - pos;
		while (n > 0)
		{
			rra(ctx);
			n--;
		}
	}
}

void	bring_to_top_b(t_ctx *ctx, int pos)
{
	int	n;

	if (pos <= ctx->b.size / 2)
	{
		n = pos;
		while (n > 0)
		{
			rb(ctx);
			n--;
		}
	}
	else
	{
		n = ctx->b.size - pos;
		while (n > 0)
		{
			rrb(ctx);
			n--;
		}
	}
}
