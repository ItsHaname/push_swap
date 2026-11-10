/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_sort_complex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/11/09 12:00:00 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	max_bits(int n)
{
	int	bits;

	bits = 0;
	while (((n - 1) >> bits) != 0)
		bits++;
	return (bits);
}

static void	push_zeros(t_ctx *ctx, int bit)
{
	int	n;

	n = ctx->a.size;
	while (n > 0)
	{
		if (((ctx->a.val[ctx->a.top] >> bit) & 1) == 0)
			pb(ctx);
		else
			ra(ctx);
		n--;
	}
}

static void	pull_back(t_ctx *ctx, int next_bit, int last)
{
	int	n;

	n = ctx->b.size;
	while (n > 0)
	{
		if (!last && ((ctx->b.val[ctx->b.top] >> next_bit) & 1) == 0)
			rb(ctx);
		else
			pa(ctx);
		n--;
	}
}

void	sort_complex(t_ctx *ctx)
{
	int	bit;
	int	bits;

	bits = max_bits(ctx->a.size);
	bit = 0;
	while (bit < bits && !(ctx->b.size == 0 && is_sorted(&ctx->a)))
	{
		push_zeros(ctx, bit);
		pull_back(ctx, bit + 1, bit + 1 == bits);
		bit++;
	}
}
