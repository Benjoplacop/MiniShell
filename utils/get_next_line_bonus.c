/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:02:39 by mbilly            #+#    #+#             */
/*   Updated: 2023/07/07 12:19:40 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(int fd, char *str)
{
	char	*tmp;
	int		byteread;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (0);
	byteread = 1;
	while (ft_strchr(str, '\n') == 0 && byteread != 0 && str)
	{
		byteread = read(fd, tmp, BUFFER_SIZE);
		if (byteread == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[byteread] = '\0';
		str = ft_strjoin2(str, tmp);
	}
	free(tmp);
	return (str);
}

static char	*left_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	res = ft_calloc(sizeof(char), i + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	return (res);
}

static char	*right_line(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	res = ft_calloc(sizeof(char), ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		res[j++] = str[i++];
	free(str);
	return (res);
}

char	*get_next_line(int fd, int fin)
{
	static char	*str[1024];
	char		*line;

	if (fin == 1)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = left_line(str[fd]);
	str[fd] = right_line(str[fd]);
	return (line);
}
