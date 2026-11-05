/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_ops_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:25:57 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 00:25:57 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack *s)
{
	int	x;
	int	bottom;

	if (s->size < 2)
		return ;
	x = s->val[s->top];
	s->top = (s->top + 1) % s->cap;
	bottom = (s->top + s->size - 1) % s->cap;
	s->val[bottom] = x;
}

void	ra(t_ctx *ctx)
{
	rotate(&ctx->a);
	write(1, "ra\n", 3);
	ctx->counts[OP_RA]++;
	ctx->total++;
}

void	rb(t_ctx *ctx)
{
	rotate(&ctx->b);
	write(1, "rb\n", 3);
	ctx->counts[OP_RB]++;
	ctx->total++;
}

void	rr(t_ctx *ctx)
{
	rotate(&ctx->a);
	rotate(&ctx->b);
	write(1, "rr\n", 3);
	ctx->counts[OP_RR]++;
	ctx->total++;
}
