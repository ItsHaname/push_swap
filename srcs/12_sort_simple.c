/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_sort_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 02:34:22 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 02:34:22 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_simple(t_ctx *ctx)
{
	while (ctx->a.size > 0 && !is_sorted(&ctx->a))
	{
		bring_to_top_a(ctx, find_min_pos(&ctx->a));
		pb(ctx);
	}
	while (ctx->b.size > 0)
		pa(ctx);
}
