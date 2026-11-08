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

static void	radix_a(t_ctx *ctx, int lo, int len);
static void	radix_b(t_ctx *ctx, int lo, int len);

static void	bucket_a(t_ctx *ctx, t_radix *r, int lo)
{
	int	v;

	while (r->pushed < r->d2 - lo)
	{
		v = ctx->a.val[ctx->a.top];
		if (v >= r->d2 && ++r->nbig)
		{
			if (r->rot)
				rr(ctx);
			else
				ra(ctx);
		}
		else if (++r->pushed)
		{
			if (r->rot)
				rb(ctx);
			pb(ctx);
		}
		r->rot = (v >= r->d1 && v < r->d2);
		r->nmid += r->rot;
	}
	if (r->rot)
		rb(ctx);
}

static void	bucket_b(t_ctx *ctx, t_radix *r, int lo, int len)
{
	int	v;

	while (r->pushed < lo + len - r->d1)
	{
		v = ctx->b.val[ctx->b.top];
		if (v < r->d1 && ++r->nbig)
		{
			if (r->rot)
				rr(ctx);
			else
				rb(ctx);
		}
		else if (++r->pushed)
		{
			if (r->rot)
				ra(ctx);
			pa(ctx);
		}
		r->rot = (v >= r->d1 && v < r->d2);
		r->nmid += r->rot;
	}
	if (r->rot)
		ra(ctx);
}

static void	radix_a(t_ctx *ctx, int lo, int len)
{
	t_radix	r;

	if (top_sorted(&ctx->a, len, 1))
		return ;
	if (len <= 3)
		return (sort_top_a(ctx, len));
	r = make_radix(lo, len, ctx->a.size == len);
	bucket_a(ctx, &r, lo);
	unrotate(ctx, r.nbig * !r.whole, r.nmid * (ctx->b.size != r.nmid));
	radix_a(ctx, r.d2, lo + len - r.d2);
	radix_b(ctx, r.d1, r.d2 - r.d1);
	radix_b(ctx, lo, r.d1 - lo);
}

static void	radix_b(t_ctx *ctx, int lo, int len)
{
	t_radix	r;

	if (top_sorted(&ctx->b, len, 0) || len <= 3)
		return (push_back_b(ctx, len));
	r = make_radix(lo, len, ctx->b.size == len);
	bucket_b(ctx, &r, lo, len);
	radix_a(ctx, r.d2, lo + len - r.d2);
	unrotate(ctx, r.nmid, r.nbig * !r.whole);
	radix_a(ctx, r.d1, r.d2 - r.d1);
	radix_b(ctx, lo, r.d1 - lo);
}

void	sort_complex(t_ctx *ctx)
{
	radix_a(ctx, 0, ctx->a.size);
}
