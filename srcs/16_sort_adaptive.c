/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_sort_adaptive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_ctx *ctx)
{
	if (ctx->a.size <= 5)
	{
		ctx->used = STRAT_SIMPLE;
		sort_small(ctx);
	}
	else if (ctx->disorder < LOW_DISORDER)
	{
		ctx->used = STRAT_SIMPLE;
		sort_simple(ctx);
	}
	else if (ctx->disorder < HIGH_DISORDER)
	{
		ctx->used = STRAT_MEDIUM;
		sort_medium(ctx);
	}
	else
	{
		ctx->used = STRAT_COMPLEX;
		sort_complex(ctx);
	}
}

void	run_strategy(t_ctx *ctx)
{
	ctx->used = ctx->strategy;
	if (ctx->strategy == STRAT_SIMPLE)
		sort_simple(ctx);
	else if (ctx->strategy == STRAT_MEDIUM)
		sort_medium(ctx);
	else if (ctx->strategy == STRAT_COMPLEX)
		sort_complex(ctx);
	else
		sort_adaptive(ctx);
}
