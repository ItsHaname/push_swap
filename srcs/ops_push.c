/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:58:27 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 23:58:27 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack *from, t_stack *to)
{
	int	i;
	int	x;

	if (from->size == 0)
		return ;
	x = from->val[0];
	i = 0;
	while (i < from->size - 1)
	{
		from->val[i] = from->val[i + 1];
		i++;
	}
	from->size--;
	i = to->size;
	while (i > 0)
	{
		to->val[i] = to->val[i - 1];
		i--;
	}
	to->val[0] = x;
	to->size++;
}

void	pa(t_ctx *ctx)
{
	push(&ctx->b, &ctx->a);
	write(1, "pa\n", 3);
	ctx->counts[OP_PA]++;
	ctx->total++;
}

void	pb(t_ctx *ctx)
{
	push(&ctx->a, &ctx->b);
	write(1, "pb\n", 3);
	ctx->counts[OP_PB]++;
	ctx->total++;
}
