/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:04:45 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/10 19:42:32 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_in_and_out_child(t_cmd *cmd1, t_copy *copy, int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	exec_cmd(cmd1, copy);
	free_fork(copy);
}

void	redir_in_and_out(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy, char *sep)
{
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
	pid_t	process1;
	char	*save;

	save = ft_strdup(cmd2->new_token);
	free(cmd2->new_token);
	cmd2->new_token = take_last_redir(save, 0, &sep, '<');
	if (check_sep(sep) == S_LEFT_REDIR || check_sep(sep) == D_LEFT_REDIR)
	{
		fd_out = open_files_in_and_out(cmd2, sep, &fd_in, save);
		if (pipe(pipefd) < 0)
			return ;
		process1 = fork();
		if (process1 == 0)
		{
			redir_in_and_out_child(cmd1, copy, fd_in, fd_out);
			close_all(pipefd, fd_in, fd_out);
			exit(1);
		}
		else
			waitpid(process1, NULL, 0);
	}
}

void	redir_cond(t_cmd *cmd2, char **sep, char *save)
{
	int	i;
	int	l_redir;
	int	r_redir;

	i = 0;
	l_redir = 0;
	r_redir = 0;
	while (cmd2->new_token[i])
	{
		if (cmd2->new_token[i] == '<')
			l_redir++;
		if (cmd2->new_token[i] == '>')
			r_redir++;
		i++;
	}
	if (ft_strncmp(*sep, "<", 1) == 0 && l_redir > 0 && r_redir == 0)
	{
		free(cmd2->new_token);
		cmd2->new_token = take_last_redir(save, 0, sep, '<');
	}
	else if (ft_strncmp(*sep, ">", 1) == 0 && l_redir == 0 && r_redir > 0)
	{
		free(cmd2->new_token);
		cmd2->new_token = take_last_redir(save, 0, sep, '>');
	}
}

int	redir_cond2(t_cmd *cmd1, t_cmd *cmd2, char **sep, t_copy *copy)
{
	int	i;
	int	l_redir;
	int	r_redir;

	i = -1;
	l_redir = 0;
	r_redir = 0;
	while (cmd2->new_token[++i])
	{
		if (cmd2->new_token[i] == '<')
			l_redir++;
		if (cmd2->new_token[i] == '>')
			r_redir++;
	}
	if (ft_strncmp(*sep, "<", 1) == 0 && r_redir > 0)
	{
		redir_in_and_out(cmd1, cmd2, copy, *sep);
		return (-1);
	}
	else if (ft_strncmp(*sep, ">", 1) == 0 && l_redir > 0)
	{
		redir_in_and_out(cmd1, cmd2, copy, *sep);
		return (-1);
	}
	return (0);
}

void	redir(t_cmd *cmd1, char *sep, t_cmd *cmd2, t_copy *copy)
{
	char	*save;
	char	*sep2;

	save = ft_strdup(cmd2->new_token);
	sep2 = ft_strdup(sep);
	redir_cond(cmd2, &sep2, save);
	free(save);
	if (redir_cond2(cmd1, cmd2, &sep2, copy) == -1)
	{
		free(sep2);
		return ;
	}
	if (check_sep(sep2) == S_RIGHT_REDIR)
		s_right_redir(cmd1, cmd2, copy);
	else if (check_sep(sep2) == D_RIGHT_REDIR)
		d_right_redir(cmd1, cmd2, copy);
	else if (check_sep(sep2) == S_LEFT_REDIR)
		s_left_redir(cmd1, cmd2, copy);
	else if (check_sep(sep2) == D_LEFT_REDIR)
		d_left_redir(cmd1, cmd2, copy);
	free(sep2);
}
