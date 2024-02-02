/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:44:05 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/22 14:43:46 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_n(char *line, int i)
{
	if (line[i] && line[i] == '-')
	{
		i++;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] != 'n')
				return (0);
			i++;
		}
	}
	return (i);
}

char	*copie_arg(char *envp, int len)
{
	char	*arg_return;
	int		j;

	j = 0;
	while (envp[j + len + 1])
		j++;
	arg_return = malloc(sizeof(char) * (j + 1));
	arg_return[j] = '\0';
	j = 0;
	while (envp[j + len + 1])
	{
		arg_return[j] = envp[j + len + 1];
		j++;
	}
	return (arg_return);
}

int	compare_var(char *arg, char *envp)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (envp[i] != arg[i])
			return (1);
		i++;
	}
	if (envp[i] != '=')
		return (1);
	return (0);
}

char	*take_var_env(char *arg, char **envp)
{
	int		i;
	int		len;
	char	*arg_return;
	int		j;

	arg_return = NULL;
	len = ft_strlen(arg);
	i = 0;
	j = 0;
	while (envp[j])
		j++;
	while (envp[i])
	{
		if (compare_var(arg, envp[i]) == 0)
		{
			arg_return = copie_arg(envp[i], len);
			break ;
		}
		i++;
	}
	if (i == j)
		arg_return = ft_strdup("\0");
	return (arg_return);
}

int	take_path(char *arg, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(arg, envp[i], len) == 0)
			return (0);
		i++;
	}
	return (1);
}
