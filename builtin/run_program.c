/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:57:40 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/26 17:55:42 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**minishell_test(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			tmp = ft_itoa(ft_atoi(&envp[i][6]) + 1);
			free(envp[i]);
			envp[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		i++;
	}
	return (envp);
}

static char	*join_split_path(char *split_path, char *command)
{
	split_path = ft_strjoin2(split_path, "/");
	split_path = ft_strjoin2(split_path, command);
	return (split_path);
}

static void	split_path_func(char **split_path, char **envp, char **command)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	j = 0;
	while (split_path[j])
		j++;
	while (split_path[++i])
	{
		split_path[i] = join_split_path(split_path[i], command[0]);
		if (access(split_path[i], F_OK) == 0)
			break ;
	}
	if (i == j)
	{
		printf("%s : Command not found\n", command[0]);
		exit(127);
	}
	ret = execve(split_path[i], command, envp);
	if (ret == -1)
	{
		ft_putstr_fd("execve", 2);
		exit(127);
	}
}

int	take_and_run_path(char *path, char **command, char **envp)
{
	char	**split_path;
	int		error;
	pid_t	pid;

	split_path = ft_split(path, ':');
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork", 2);
		exit(0);
		return (1);
	}
	else if (pid == 0)
		split_path_func(split_path, envp, command);
	else
	{
		waitpid(pid, &error, 0);
		if (error != 0)
			g_ft_error = ((error & 0xFF00) >> 8);
	}
	free_split(command);
	free_split(split_path);
	free(path);
	return (0);
}

int	run_program(char **args, char **envp)
{
	int	pid;
	int	ret;

	pid = fork();
	ret = 0;
	if (pid == 0)
	{
		ret = execve(args[0], args, envp);
		if (ret == -1)
		{
			printf("Error: Unable to execute %s.\n", args[0]);
			return (ret);
		}
	}
	else
	{
		waitpid(pid, &ret, 0);
		if (ret != 0)
			g_ft_error = ((ret & 0xFF00) >> 8);
	}
	free_split(args);
	return (ret);
}
