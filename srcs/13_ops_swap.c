/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_ops_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:37:28 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 23:37:28 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *s)
{
	int	tmp;
	int	second;

	if (s->size >= 2)
	{
		second = (s->top + 1) % s->cap;
		tmp = s->val[s->top];
		s->val[s->top] = s->val[second];
		s->val[second] = tmp;
	}
}

void	sa(t_ctx *ctx)
{
	swap(&ctx->a);
	write(1, "sa\n", 3);
	ctx->counts[OP_SA]++;
	ctx->total++;
}

void	sb(t_ctx *ctx)
{
	swap(&ctx->b);
	write(1, "sb\n", 3);
	ctx->counts[OP_SB]++;
	ctx->total++;
}

void	ss(t_ctx *ctx)
{
	swap(&ctx->a);
	swap(&ctx->b);
	write(1, "ss\n", 3);
	ctx->counts[OP_SS]++;
	ctx->total++;
}
