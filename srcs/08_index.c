/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 19:26:43 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/10/30 19:26:43 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rank_of(t_stack *s, int i)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < s->size)
	{
		if (s->val[(s->top + j) % s->cap] < s->val[(s->top + i) % s->cap])
			count++;
		j++;
	}
	return (count);
}

void	assign_index(t_ctx *ctx)
{
	int	*index;
	int	i;

	index = malloc(sizeof(int) * ctx->a.size);
	if (!index)
		error_exit(ctx);
	i = 0;
	while (i < ctx->a.size)
	{
		index[i] = rank_of(&ctx->a, i);
		i++;
	}
	free(ctx->a.val);
	ctx->a.val = index;
	ctx->a.top = 0;
}
