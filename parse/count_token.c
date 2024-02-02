/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:15:49 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/03 14:23:25 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_token4(char *str, int *i, int *token, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
	if ((*i) >= (int)ft_strlen(str))
	{
		(*token)++;
		return (-1);
	}
	if (ft_isalpha(str[*i]) == 1)
		(*token)++;
	return (0);
}

static void	count_token3(char *str, int *i, int *token)
{
	if (str[*i + 1] == ')')
	{
		(*token)++;
		(*i)++;
	}
	if (str[*i + 1] == '\0')
		(*token)++;
	(*i)++;
}

static int	count_token2(char *str, int *i, int *token)
{
	if (str[*i] == '(')
	{
		if (str[*i + 1] == ')')
		{
			*i = *i + 2;
			(*token)++;
		}
		(*token)++;
	}
	else if (str[*i] == ')')
		count_token3(str, i, token);
	else if (str[*i] && str[*i + 1] && (str[*i] == str[*i + 1]))
	{
		(*token)++;
		(*i)++;
	}
	else
		(*token)++;
	if (str[*i] && (str[*i + 1] == ' ' || str[*i + 1] == '\t'))
		(*i)++;
	(*i)++;
	if (*i >= (int)ft_strlen(str))
		return (-1);
	return (0);
}

int	count_token(char *str)
{
	int	i;
	int	token;

	token = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && ft_strchr("<>()|& ", str[i]))
		{
			if (count_token2(str, &i, &token) == -1)
				break ;
		}
		else if (str[i] && (str[i] == '\'' || str[i] == '"'))
			if (count_token4(str, &i, &token, str[i]) == -1)
				break ;
		while ((str[i] && ft_strchr("\'\"<>()|& ", str[i]) == NULL))
			i++;
		if (str[i] != '(')
			token++;
	}
	return (token);
}
