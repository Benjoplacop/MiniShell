/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:41:53 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/12 12:31:11 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_tab(char **env, int i)
{
	int	j;

	j = 0;
	while (env[j])
	{
		ft_putstr_fd(env[j], 1);
		if (j != i - 1)
			ft_putchar_fd('\n', 1);
		j++;
	}
	free_split(env);
	write(1, "\n", 1);
}

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	swap(char **env, int j)
{
	char	*tmp;

	tmp = env[j];
	env[j] = env[j + 1];
	env[j + 1] = tmp;
	return (1);
}

static void	print_var_alpha(char **envp)
{
	int		i;
	int		j;
	int		var;
	char	**env;

	j = 0;
	var = 0;
	env = get_dup_env(envp);
	i = count_env(envp);
	while (j < i - 1)
	{
		if (ft_strncmp(env[j], env[j + 1], 300) > 0)
			var = swap(env, j);
		j++;
		if (j == i - 1)
		{
			if (var != 1)
				break ;
			j = 0;
			var = 0;
		}
	}
	print_tab(env, i);
}

char	**export_var(char *line, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j] != '=' && line[j])
		j++;
	if (line[j] == '\0')
	{
		if (ft_strncmp(line, "export\0", 7) == 0)
			print_var_alpha(env);
		return (env);
	}
	while (env[i])
	{
		if (ft_strncmp(line + 7, env[i], j - 7) == 0)
		{
			free(env[i]);
			j = -1;
			break ;
		}
		i++;
	}
	env = modif_env(env, &j, &i, line);
	return (env);
}
