/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by haait-ba         ###   ########.fr       */
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

void	sort_complex(t_ctx *ctx)
{
	int	n;
	int	bit;
	int	bits;
	int	j;

	n = ctx->a.size;
	bits = max_bits(n);
	bit = 0;
	while (bit < bits && !is_sorted(&ctx->a))
	{
		j = 0;
		while (j < n)
		{
			if (((ctx->a.val[0] >> bit) & 1) == 0)
				pb(ctx);
			else
				ra(ctx);
			j++;
		}
		while (ctx->b.size > 0)
			pa(ctx);
		bit++;
	}
}
