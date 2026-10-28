/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 22:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/19 22:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numberofdigits(size_t nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		size;
	size_t	nbr;

	if (n < 0)
		nbr = -(size_t)n;
	else
		nbr = (size_t)n;
	size = numberofdigits(nbr);
	if (n < 0)
		size++;
	s = malloc(sizeof(char) * size + 1);
	if (s == NULL)
		return (NULL);
	i = size;
	while (i > 0)
	{
		s[--i] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		s[0] = '-';
	s[size] = '\0';
	return (s);
}
