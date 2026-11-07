/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_ops_rev_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:48:38 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 00:48:38 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack *s)
{
	int	x;
	int	bottom;

	if (s->size < 2)
		return ;
	bottom = (s->top + s->size - 1) % s->cap;
	x = s->val[bottom];
	s->top = (s->top - 1 + s->cap) % s->cap;
	s->val[s->top] = x;
}

void	rra(t_ctx *ctx)
{
	reverse_rotate(&ctx->a);
	write(1, "rra\n", 4);
	ctx->counts[OP_RRA]++;
	ctx->total++;
}

void	rrb(t_ctx *ctx)
{
	reverse_rotate(&ctx->b);
	write(1, "rrb\n", 4);
	ctx->counts[OP_RRB]++;
	ctx->total++;
}

void	rrr(t_ctx *ctx)
{
	reverse_rotate(&ctx->a);
	reverse_rotate(&ctx->b);
	write(1, "rrr\n", 4);
	ctx->counts[OP_RRR]++;
	ctx->total++;
}
