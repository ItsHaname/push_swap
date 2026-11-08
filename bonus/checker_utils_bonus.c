/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/08 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	read_line(char *buf)
{
	char	c;
	int		i;
	int		r;

	i = 0;
	r = read(0, &c, 1);
	while (r == 1 && c != '\n')
	{
		if (i < 4)
			buf[i++] = c;
		r = read(0, &c, 1);
	}
	buf[i] = '\0';
	if (r != 1 && i == 0)
		return (-1);
	return (i);
}

int	apply_swap_push(t_ctx *ctx, char *op)
{
	if (ft_strncmp(op, "sa", 3) == 0)
		swap(&ctx->a);
	else if (ft_strncmp(op, "sb", 3) == 0)
		swap(&ctx->b);
	else if (ft_strncmp(op, "ss", 3) == 0)
	{
		swap(&ctx->a);
		swap(&ctx->b);
	}
	else if (ft_strncmp(op, "pa", 3) == 0)
		push(&ctx->b, &ctx->a);
	else if (ft_strncmp(op, "pb", 3) == 0)
		push(&ctx->a, &ctx->b);
	else
		return (0);
	return (1);
}

int	apply_rotate(t_ctx *ctx, char *op)
{
	if (ft_strncmp(op, "ra", 4) == 0)
		rotate(&ctx->a);
	else if (ft_strncmp(op, "rb", 4) == 0)
		rotate(&ctx->b);
	else if (ft_strncmp(op, "rr", 4) == 0)
	{
		rotate(&ctx->a);
		rotate(&ctx->b);
	}
	else if (ft_strncmp(op, "rra", 4) == 0)
		reverse_rotate(&ctx->a);
	else if (ft_strncmp(op, "rrb", 4) == 0)
		reverse_rotate(&ctx->b);
	else if (ft_strncmp(op, "rrr", 4) == 0)
	{
		reverse_rotate(&ctx->a);
		reverse_rotate(&ctx->b);
	}
	else
		return (0);
	return (1);
}

int	apply_op(t_ctx *ctx, char *op)
{
	return (apply_swap_push(ctx, op) || apply_rotate(ctx, op));
}
