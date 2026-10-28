/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 22:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/10/19 22:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_all(char **tab, size_t colonne)
{
	while (colonne > 0)
	{
		colonne--;
		free(tab[colonne]);
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	colonne;
	size_t	ligne;
	size_t	i;

	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	colonne = 0;
	ligne = 0;
	while (colonne < count_words(s, c))
	{
		while (s[ligne] && s[ligne] == c)
			ligne++;
		tab[colonne] = malloc(sizeof(char) * (word_len(&s[ligne], c) + 1));
		if (tab[colonne] == NULL)
			return (free_all(tab, colonne), NULL);
		i = 0;
		while (s[ligne] && s[ligne] != c)
			tab[colonne][i++] = s[ligne++];
		tab[colonne][i] = '\0';
		colonne++;
	}
	tab[colonne] = NULL;
	return (tab);
}
