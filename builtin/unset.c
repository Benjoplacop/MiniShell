/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:41:07 by bhennequ          #+#    #+#             */
/*   Updated: 2023/10/03 15:26:33 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**boucle_unset(char **envp, int i, char *name)
{
	int	j;

	j = i;
	while (envp[j + 1])
	{
		free(envp[j]);
		envp[j] = ft_strdup(envp[j + 1]);
		j++;
	}
	if (ft_strncmp(envp[j], envp[i], ft_strlen(name)) == 0)
		free(envp[j]);
	envp[j] = NULL;
	return (envp);
}

static void	increment(int *k, int *i)
{
	(*k)++;
	*i = -1;
}

static int	only_space(char *var_name)
{
	int	i;

	i = 0;
	if (ft_strncmp(var_name, "\0", 1) == 0)
		return (0);
	while (var_name[i])
	{
		if (var_name[i] != ' ' && var_name[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

char	**unset_var(char *var_name, char **envp)
{
	int		i;
	int		k;
	char	**split_tab;

	i = 0;
	k = 0;
	if (only_space(var_name) == 0)
		return (envp);
	split_tab = ft_split(var_name, ' ');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], split_tab[k], ft_strlen(split_tab[k])) == 0
			&& envp[i][ft_strlen(split_tab[k])] == '=')
		{
			envp = boucle_unset(envp, i, split_tab[k]);
			if (split_tab[k + 1])
				increment(&k, &i);
			else
				break ;
		}
		i++;
	}
	g_ft_error = 0;
	free_split(split_tab);
	return (envp);
}
