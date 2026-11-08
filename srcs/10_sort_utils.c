/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 00:56:59 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/31 00:56:59 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_pos(t_stack *s)
{
	int	i;
	int	pos;

	if (s->size == 0)
		return (-1);
	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->val[(s->top + i) % s->cap] < s->val[(s->top + pos) % s->cap])
			pos = i;
		i++;
	}
	return (pos);
}

int	find_max_pos(t_stack *s)
{
	int	i;
	int	pos;

	if (s->size == 0)
		return (-1);
	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->val[(s->top + i) % s->cap] > s->val[(s->top + pos) % s->cap])
			pos = i;
		i++;
	}
	return (pos);
}

void	bring_to_top_a(t_ctx *ctx, int pos)
{
	int	n;

	if (pos <= ctx->a.size / 2)
	{
		n = pos;
		while (n > 0)
		{
			ra(ctx);
			n--;
		}
	}
	else
	{
		n = ctx->a.size - pos;
		while (n > 0)
		{
			rra(ctx);
			n--;
		}
	}
}

/* ===================== rotate_both ======================================
** Do na rotations on a and nb rotations on b, merging them when possible.
**   n > 0  -> n times "rotate"          (ra / rb)
**   n < 0  -> -n times "reverse rotate" (rra / rrb)
**   n = 0  -> nothing on that stack
** Why: "ra" + "rb" (2 ops) has exactly the same effect as one "rr",
** and "rra" + "rrb" (2 ops) the same as one "rrr". So while BOTH stacks
** must turn in the SAME direction, we print one combined op instead of
** two -> every merge saves 1 operation.
** Example: na = 3, nb = 5  ->  rr rr rr rb rb   (5 ops instead of 8)
**          na = -2, nb = -1 ->  rrr rra         (2 ops instead of 3)
**          na = 2, nb = -2  ->  ra ra rrb rrb   (opposite directions:
**                                                nothing can be merged)
** Loop trick: "na > 0 && na--" checks first, THEN decrements, so each
** loop runs exactly na times and leaves na at 0 (same for na++ / nb).
** ======================================================================= */
void	rotate_both(t_ctx *ctx, int na, int nb)
{
	while (na > 0 && nb > 0 && na-- && nb--)
		rr(ctx);
	while (na < 0 && nb < 0 && na++ && nb++)
		rrr(ctx);
	while (na > 0 && na--)
		ra(ctx);
	while (na < 0 && na++)
		rra(ctx);
	while (nb > 0 && nb--)
		rb(ctx);
	while (nb < 0 && nb++)
		rrb(ctx);
}

void	bring_to_top_b(t_ctx *ctx, int pos)
{
	int	n;

	if (pos <= ctx->b.size / 2)
	{
		n = pos;
		while (n > 0)
		{
			rb(ctx);
			n--;
		}
	}
	else
	{
		n = ctx->b.size - pos;
		while (n > 0)
		{
			rrb(ctx);
			n--;
		}
	}
}
