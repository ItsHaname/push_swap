/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 19:26:43 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/10/30 19:26:43 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(char *arg)
{
	if (arg[0] == '-' && arg[1] == '-')
		return (1);
	return (0);
}

static void	set_strategy(t_ctx *ctx, t_strat strategy)
{
	if (ctx->strat_set == 1)
		error_exit(ctx);
	ctx->strategy = strategy;
	ctx->strat_set = 1;
}

static void	set_flag(t_ctx *ctx, char *arg)
{
	if (ft_strncmp(arg, "--simple", 9) == 0)
		set_strategy(ctx, STRAT_SIMPLE);
	else if (ft_strncmp(arg, "--medium", 9) == 0)
		set_strategy(ctx, STRAT_MEDIUM);
	else if (ft_strncmp(arg, "--complex", 10) == 0)
		set_strategy(ctx, STRAT_COMPLEX);
	else if (ft_strncmp(arg, "--adaptive", 11) == 0)
		set_strategy(ctx, STRAT_ADAPTIVE);
	else if (ft_strncmp(arg, "--bench", 8) == 0)
		ctx->bench = 1;
	else
		error_exit(ctx);
}

void	parse_flags(t_ctx *ctx, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			set_flag(ctx, argv[i]);
		i++;
	}
}
