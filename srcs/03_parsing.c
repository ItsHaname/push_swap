/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 17:36:42 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 17:36:42 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_numbers(t_ctx *ctx, int argc, char **argv)
{
	int	i;
	int	total;
	int	mot;

	total = 0;
	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			i++;
		else
		{
			mot = count_words(argv[i], ' ');
			if (mot == 0)
				error_exit(ctx);
			total += mot;
			i++;
		}
	}
	return (total);
}

static void	fill_from_arg(t_ctx *ctx, char *arg)
{
	char	**word;
	int		j;
	int		nb;
	int		ok;

	word = ft_split(arg, ' ');
	if (!word)
		error_exit(ctx);
	j = 0;
	while (word[j])
	{
		nb = safe_atoi(word[j], &ok);
		if (!ok)
		{
			free_split(word);
			error_exit(ctx);
		}
		ctx->a.val[ctx->a.size] = nb;
		ctx->a.size++;
		j++;
	}
	free_split(word);
}

void	parse_numbers(t_ctx *ctx, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i]))
			fill_from_arg(ctx, argv[i]);
		i++;
	}
}
