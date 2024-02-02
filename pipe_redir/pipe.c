/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:38:14 by mbilly            #+#    #+#             */
/*   Updated: 2023/08/12 12:23:02 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_fork(t_copy *copy)
{
	free_cmd(copy->cmd);
	free(copy->cmd->tok);
	free(copy->cmd);
	free_split(copy->envp);
	free(copy);
}

static void	ft_pipe2(t_cmd *cmd2, int fdd, t_copy *copy)
{
	int		pipefd[2];
	int		ret;
	pid_t	process;

	pipe(pipefd);
	process = fork();
	if (process == 0)
	{
		close(pipefd[0]);
		dup2(fdd, 0);
		exec_cmd(cmd2, copy);
		free_fork(copy);
		if (g_ft_error != 0)
			exit(127);
		exit(0);
	}
	else
	{
		waitpid(process, &ret, 0);
		close(pipefd[1]);
		fdd = pipefd[0];
		if (ret != 0)
			g_ft_error = ((ret & 0xFF00) >> 8);
	}
}

static void	ft_pipe_check_error(int ret, t_cmd *cmd2, int fdd, t_copy *copy)
{
	if (ret != 0)
		g_ft_error = ((ret & 0xFF00) >> 8);
	else
		ft_pipe2(cmd2, fdd, copy);
}

static int	ft_pipe_waitpid(pid_t process, int *fdd, int *pipefd)
{
	int	ret;

	waitpid(process, &ret, 0);
	close(pipefd[1]);
	*fdd = pipefd[0];
	return (ret);
}

void	ft_pipe(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy)
{
	int		pipefd[2];
	int		fdd;
	int		ret;
	pid_t	process;

	fdd = 0;
	pipe(pipefd);
	process = fork();
	if (process == 0)
	{
		dup2(fdd, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		exec_cmd(cmd1, copy);
		free_fork(copy);
		if (g_ft_error != 0)
			exit(127);
		exit(0);
	}
	else
	{
		ret = ft_pipe_waitpid(process, &fdd, pipefd);
		ft_pipe_check_error(ret, cmd2, fdd, copy);
	}
}
