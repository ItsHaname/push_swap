/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_sort_complex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_a(t_ctx *ctx, int lo, int len);
static void	sort_b(t_ctx *ctx, int lo, int len);

/* big stays in a (ra), mid -> b then rb, small -> b on top.
** a pending rb followed by an ra becomes a single rr */
static void	split_a(t_ctx *ctx, t_part *p, int lo)
{
	int	v;

	while (p->pushed < p->p2 - lo)
	{
		v = ctx->a.val[ctx->a.top];
		if (v >= p->p2 && ++p->nbig)
		{
			if (p->rot)
				rr(ctx);
			else
				ra(ctx);
		}
		else if (++p->pushed)
		{
			if (p->rot)
				rb(ctx);
			pb(ctx);
		}
		p->rot = (v >= p->p1 && v < p->p2);
		p->nmid += p->rot;
	}
	if (p->rot)
		rb(ctx);
}

/* big -> a, mid -> a then ra, small stays in b (rb).
** a pending ra followed by an rb becomes a single rr */
static void	split_b(t_ctx *ctx, t_part *p, int lo, int len)
{
	int	v;

	while (p->pushed < lo + len - p->p1)
	{
		v = ctx->b.val[ctx->b.top];
		if (v < p->p1 && ++p->nbig)
		{
			if (p->rot)
				rr(ctx);
			else
				rb(ctx);
		}
		else if (++p->pushed)
		{
			if (p->rot)
				ra(ctx);
			pa(ctx);
		}
		p->rot = (v >= p->p1 && v < p->p2);
		p->nmid += p->rot;
	}
	if (p->rot)
		ra(ctx);
}

/* top `len` of a holds the indexes lo .. lo+len-1 */
static void	sort_a(t_ctx *ctx, int lo, int len)
{
	t_part	p;

	if (top_sorted(&ctx->a, len, 1))
		return ;
	if (len <= 3)
		return (sort_top_a(ctx, len));
	p = make_part(lo, len, ctx->a.size == len);
	split_a(ctx, &p, lo);
	unrotate(ctx, p.nbig * !p.whole, p.nmid * (ctx->b.size != p.nmid));
	sort_a(ctx, p.p2, lo + len - p.p2);
	sort_b(ctx, p.p1, p.p2 - p.p1);
	sort_b(ctx, lo, p.p1 - lo);
}

/* top `len` of b holds the indexes lo .. lo+len-1 */
static void	sort_b(t_ctx *ctx, int lo, int len)
{
	t_part	p;

	if (top_sorted(&ctx->b, len, 0) || len <= 3)
		return (push_back_b(ctx, len));
	p = make_part(lo, len, ctx->b.size == len);
	split_b(ctx, &p, lo, len);
	sort_a(ctx, p.p2, lo + len - p.p2);
	unrotate(ctx, p.nmid, p.nbig * !p.whole);
	sort_a(ctx, p.p1, p.p2 - p.p1);
	sort_b(ctx, lo, p.p1 - lo);
}

void	sort_complex(t_ctx *ctx)
{
	sort_a(ctx, 0, ctx->a.size);
}
