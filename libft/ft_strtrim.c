/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 22:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/19 22:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;

	if (s1 == NULL || set == NULL)
		return (NULL);
	debut = 0;
	while (s1[debut] && in_set(s1[debut], set))
		debut++;
	fin = ft_strlen(s1);
	while (fin > debut && in_set(s1[fin - 1], set))
		fin--;
	return (ft_substr(s1, debut, fin - debut));
}
