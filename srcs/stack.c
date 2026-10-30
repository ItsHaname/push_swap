/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:47:44 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 13:47:44 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_ctx(t_ctx *ctx)
{
	int	i;

	ctx->a.val = NULL;
	ctx->a.size = 0;
	ctx->b.val = NULL;
	ctx->b.size = 0;
	ctx->total = 0;
	i = 0;
	while (i < OP_COUNT)
	{
		ctx->counts[i] = 0;
		i++;
	}
	ctx->disorder = 0;
	ctx->strategy = STRAT_ADAPTIVE;
	ctx->used = STRAT_ADAPTIVE;
	ctx->strat_set = 0;
	ctx->bench = 0;
}

void	free_ctx(t_ctx *ctx)
{
	free(ctx->a.val);
	free(ctx->b.val);
	ctx->a.val = NULL;
	ctx->b.val = NULL;
}

void	error_exit(t_ctx *ctx)
{
	free_ctx(ctx);
	write(2, "Error\n", 6);
	exit(1);
}

void	init_stacks(t_ctx *ctx, int n)
{
	ctx->a.val = malloc(sizeof(int) * n);
	ctx->b.val = malloc(sizeof(int) * n);
	if (ctx->a.val == NULL || ctx->b.val == NULL)
		error_exit(ctx);
}
