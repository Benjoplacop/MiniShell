/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:46:02 by mbilly            #+#    #+#             */
/*   Updated: 2023/02/14 14:48:25 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	nb_word(char const *s, char c)
{
	int	nb_word;
	int	i;
	int	etat;

	etat = 0;
	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] != c && etat == 0)
		{
			etat = 1;
			nb_word++;
		}
		else if (s[i] == c)
			etat = 0;
		i++;
	}
	return (nb_word);
}

static char	**fill_tab(char const *s, char c, char **tmp)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[j] && s[j] != c)
			j++;
		if (s[i] != '\0')
			*tmp++ = ft_substr(s, (unsigned int) i, (size_t)(j - i));
		i = j;
		if (s[i])
			i++;
	}
	*tmp = NULL;
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;

	if (!s)
		return (NULL);
	tmp = ft_calloc(nb_word(s, c) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	fill_tab(s, c, tmp);
	return (tmp);
}
