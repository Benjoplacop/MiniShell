/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:00:58 by mbilly            #+#    #+#             */
/*   Updated: 2023/02/10 14:35:19 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) +1);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		tmp[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tmp[j++] = s2[i++];
	tmp[j] = 0;
	return (tmp);
}
