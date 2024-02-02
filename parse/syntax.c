/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:56:23 by mbilly            #+#    #+#             */
/*   Updated: 2023/09/15 04:17:14 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (i == inside_quote(str, i))
			i++;
		else
			i = inside_quote(str, i);
		if (i == (int)ft_strlen(str))
			break ;
		while (str[i] && (str[i] == c || str[i] == ' '))
		{
			if (str[i] == c)
				j++;
			if (j >= 3)
				return (-1);
			i++;
		}
		if (i == (int)ft_strlen(str))
			break ;
	}
	return (0);
}

static int	check_and_two(int i, char *str)
{
	int	j;

	j = 0;
	while (str[i] == '&')
	{
		i++;
		j++;
	}
	if (j > 0 && j != 2)
		return (-1);
	i++;
	return (i);
}

int	check_and(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '&')
		return (-1);
	while (str[i])
	{
		if (i == inside_quote(str, i))
			i++;
		else
			i = inside_quote(str, i);
		if (i >= (int)ft_strlen(str))
			break ;
		while (str[i] && (str[i] == '&' || str[i] == ' '))
		{
			i = check_and_two(i, str);
			if (i == -1)
				return (-1);
		}
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (0);
}

int	check_pipe2(char *str, int *i)
{
	int	j;

	if (str[*i + 1] && str[*i + 1] == '|')
	{
		if (str[*i + 2] && ft_strchr("|<>&", str[*i + 2]))
			return (-1);
	}
	else
	{
		j = *i + 1;
		if (str[j] == ' ')
		{
			while (str[j] == ' ')
				j++;
			if (str[j] == '|')
				return (-1);
		}
	}
	return (0);
}

int	check_pipe(char *str, int i)
{
	if (str[0] == '|')
		return (-1);
	while (str[++i] && (str[i] == ' ' || str[i] == '>' \
				|| str[i] == '<' || str[i] == '|' || str[i] == '&'))
		if (str[i] == '|')
			return (-1);
	while (str[i])
	{
		if (i == inside_quote(str, i))
			i++;
		else
			i = inside_quote(str, i);
		if (i == (int)ft_strlen(str))
			break ;
		if (str[i] && str[i] == '|')
			if (check_pipe2(str, &i) == -1)
				return (-1);
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (check_after_last_pipe(str, i));
}
