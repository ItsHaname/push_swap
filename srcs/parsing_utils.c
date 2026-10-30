/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 15:20:32 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/30 15:20:32 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	safe_atoi(char *s, int *ok)
{
	long	res;
	int		sign;
	int		i;

	*ok = 0;
	res = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		if (res * sign > 2147483647 || res * sign < -2147483648)
			return (0);
		i++;
	}
	if (s[i] != '\0')
		return (0);
	*ok = 1;
	return ((int)(res * sign));
}

int	has_duplicates(t_stack *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->size - 1)
	{
		j = i + 1;
		while (j < s->size)
		{
			if (s->val[i] == s->val[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
