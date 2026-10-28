/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 22:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/19 22:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			tab[12];
	unsigned int	nbr;
	int				i;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		nbr = -(unsigned int)n;
		write(fd, "-", 1);
	}
	else
		nbr = (unsigned int)n;
	i = 0;
	if (n == 0)
		tab[i++] = '0';
	while (nbr > 0)
	{
		tab[i] = nbr % 10 + '0';
		nbr = nbr / 10;
		i++;
	}
	while (i > 0)
		write(fd, &tab[--i], 1);
}
