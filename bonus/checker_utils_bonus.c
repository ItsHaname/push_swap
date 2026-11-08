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

/* Read one line of stdin into buf (buf must have 5 cells).
** - read() one char at a time until '\n' or end of input
** - keep at most 4 chars: a real op has max 3, so a 4th char means
**   "too long" ("rrab" -> Error, instead of being cut to "rra")
** - r keeps read's answer: 1 = got a char, 0 = end, -1 = error
** Returns the length of the line, or -1 when there is nothing left.
** An empty line "\n" returns 0 -> apply_op("") fails -> Error. */
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

/* sa sb ss pa pb. Uses the SILENT primitives (swap, push), not sa()/pb()
** which would print. Compare 3 chars = 2 letters + '\0', so the line
** must be exactly the op. Returns 1 if recognised, 0 otherwise. */
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

/* ra rb rr rra rrb rrr: exactly the same idea as apply_swap_push.
** Compare 4 chars (3 letters + '\0') so "rra" is never taken for "rr". */
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

/* || stops at the first true: if it was a swap/push, rotations are not
** even tried. 0 from both = unknown op. */
int	apply_op(t_ctx *ctx, char *op)
{
	return (apply_swap_push(ctx, op) || apply_rotate(ctx, op));
}
