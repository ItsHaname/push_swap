/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 18:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/01 18:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_percent(long x)
{
	ft_putnbr_fd((int)(x / 100), 2);
	ft_putchar_fd('.', 2);
	if (x % 100 < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd((int)(x % 100), 2);
	ft_putchar_fd('%', 2);
}

static void	print_count(char *name, int n)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(n, 2);
	ft_putchar_fd(' ', 2);
}

static void	print_strategy(t_ctx *ctx)
{
	if (ctx->strategy == STRAT_SIMPLE)
		ft_putstr_fd("Simple", 2);
	else if (ctx->strategy == STRAT_MEDIUM)
		ft_putstr_fd("Medium", 2);
	else if (ctx->strategy == STRAT_COMPLEX)
		ft_putstr_fd("Complex", 2);
	else
		ft_putstr_fd("Adaptive", 2);
	ft_putstr_fd(" / ", 2);
	if (ctx->used == STRAT_SIMPLE)
		ft_putstr_fd("O(n^2)", 2);
	else if (ctx->used == STRAT_MEDIUM)
		ft_putstr_fd("O(n√n)", 2);
	else
		ft_putstr_fd("O(n log n)", 2);
}

void	print_bench(t_ctx *ctx)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	print_percent(ctx->disorder);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	print_strategy(ctx);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd(ctx->total, 2);
	ft_putstr_fd("\n[bench] ", 2);
	print_count("sa", ctx->counts[OP_SA]);
	print_count("sb", ctx->counts[OP_SB]);
	print_count("ss", ctx->counts[OP_SS]);
	print_count("pa", ctx->counts[OP_PA]);
	print_count("pb", ctx->counts[OP_PB]);
	ft_putstr_fd("\n[bench] ", 2);
	print_count("ra", ctx->counts[OP_RA]);
	print_count("rb", ctx->counts[OP_RB]);
	print_count("rr", ctx->counts[OP_RR]);
	print_count("rra", ctx->counts[OP_RRA]);
	print_count("rrb", ctx->counts[OP_RRB]);
	print_count("rrr", ctx->counts[OP_RRR]);
	ft_putchar_fd('\n', 2);
}
