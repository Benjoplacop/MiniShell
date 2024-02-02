/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:00:15 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/31 19:53:48 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**modif_env(char **env, int *j, int *i, char *line)
{
	if (*j != -1)
	{
		env = realloc_split(env);
		env[*i] = ft_strdup(line + 7);
		env[*i + 1] = NULL;
	}
	else
		env[*i] = ft_strdup(line + 7);
	return (env);
}

char	**get_dup_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_ft_error = 130;
	}
	else if (signum == SIGQUIT)
	{
		g_ft_error = 127;
		ft_putstr_fd("\033[2D  \033[2D", 1);
		return ;
	}
}

static char	*color_prompt(char *str)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;36m", str);
	prompt = ft_strjoin2(prompt, " ✗\033[0m ");
	free(str);
	return (prompt);
}

void	prompt(t_copy *copy)
{
	char	*line;
	char	*promptstr;

	while (1)
	{
		promptstr = color_prompt(pwd());
		line = readline(promptstr);
		free(promptstr);
		if (line == NULL)
		{
			if (copy->envp != NULL)
			{
				free_split(copy->envp);
				free(copy);
			}
			break ;
		}
		if (ft_strncmp(line, "", 1) != 0
			&& check_only_space(line, copy) == 0)
			init_and_parse(line, copy);
		if (line)
			add_history(line);
		if (line)
			free(line);
	}
}
