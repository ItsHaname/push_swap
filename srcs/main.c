/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-mgh <sael-mgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:00:00 by sael-mgh          #+#    #+#             */
/*   Updated: 2026/11/04 12:00:00 by sael-mgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	int		n;

	if (argc < 2)
		return (0);
	init_ctx(&ctx);
	parse_flags(&ctx, argc, argv);
	n = count_numbers(&ctx, argc, argv);
	if (n == 0)
		return (0);
	init_stacks(&ctx, n);
	parse_numbers(&ctx, argc, argv);
	if (has_duplicates(&ctx.a))
		error_exit(&ctx);
	assign_index(&ctx);
	ctx.disorder = compute_disorder(&ctx.a);
	if (!is_sorted(&ctx.a))
		run_strategy(&ctx);
	if (ctx.bench)
		print_bench(&ctx);
	free_ctx(&ctx);
	return (0);
}
