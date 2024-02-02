/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:18:31 by mbilly            #+#    #+#             */
/*   Updated: 2023/07/07 12:28:58 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dup_redir_in2(t_cmd *cmd1, int fdd, t_copy *copy)
{
	int		pipefd[2];
	pid_t	process;

	pipe(pipefd);
	process = fork();
	if (process == 0)
	{
		close(pipefd[0]);
		dup2(fdd, 0);
		exec_cmd(cmd1, copy);
		free_fork(copy);
		exit(1);
	}
	else
	{
		waitpid(process, NULL, 0);
		close(pipefd[1]);
		fdd = pipefd[0];
	}
}

void	ft_dup_redir_in(t_cmd *cmd1, int fd_in, t_copy *copy)
{
	int		pipefd[2];
	int		fdd;
	pid_t	process;

	fdd = 0;
	pipe(pipefd);
	process = fork();
	if (process == 0)
	{
		dup2(fd_in, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		exec_cmd(cmd1, copy);
		free_fork(copy);
		exit(1);
	}
	else
	{
		waitpid(process, NULL, 0);
		close(pipefd[1]);
		fdd = pipefd[0];
		ft_dup_redir_in2(cmd1, fdd, copy);
	}
}

void	s_right_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy)
{
	int	new_fd;
	int	fd_out;

	fd_out = open(cmd2->new_token, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out < 0)
	{
		ft_putstr_fd("Open file failed (cmd > file)\n", 2);
		return ;
	}
	if (cmd1->new_token[0] == '\0')
		return ;
	new_fd = dup(1);
	dup2(fd_out, 1);
	exec_cmd(cmd1, copy);
	dup2(new_fd, 1);
	close(new_fd);
	close(fd_out);
}

void	s_left_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy)
{
	int	fd_in;

	fd_in = open(cmd2->new_token, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("Open file failed (cmd < file)\n", 2);
		return ;
	}
	if (cmd1->new_token[0] != '\0')
		ft_dup_redir_in(cmd1, fd_in, copy);
	close(fd_in);
}
