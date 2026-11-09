/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/08 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	reject_flags(t_ctx *ctx, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			error_exit(ctx);
		i++;
	}
}

static void	print_result(t_ctx *ctx)
{
	if (is_sorted(&ctx->a) && ctx->b.size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	char	buf[5];
	int		n;

	if (argc < 2)
		return (0);
	init_ctx(&ctx);
	reject_flags(&ctx, argc, argv);
	n = count_numbers(&ctx, argc, argv);
	if (n == 0)
		return (0);
	init_stacks(&ctx, n);
	parse_numbers(&ctx, argc, argv);
	if (has_duplicates(&ctx.a) == 1)
		error_exit(&ctx);
	while (read_line(buf) != -1)
	{
		if (apply_op(&ctx, buf) == 0)
			error_exit(&ctx);
	}
	print_result(&ctx);
	free_ctx(&ctx);
	return (0);
}
