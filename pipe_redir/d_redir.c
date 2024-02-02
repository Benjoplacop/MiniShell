/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:28:17 by mbilly            #+#    #+#             */
/*   Updated: 2023/09/14 22:15:03 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_file(char *fd, char *limiter)
{
	int		tmp;
	char	*line;

	tmp = open(fd, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tmp < 0)
		ft_putstr_fd("Open heredoc file failed", 2);
	while (1)
	{
		write(2, "heredoc> ", 9);
		line = get_next_line(0, 0);
		if (line == NULL)
			break ;
		if (ft_strncmp(limiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			line = get_next_line(0, 1);
			break ;
		}
		write(tmp, line, ft_strlen(line));
		free(line);
	}
	close(tmp);
}

void	d_right_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy)
{
	int	new_fd;
	int	fd_out;

	fd_out = open(cmd2->new_token, O_CREAT | O_APPEND | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out < 0)
	{
		ft_putstr_fd("Open file failed (cmd >> file)\n", 2);
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

void	d_left_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy)
{
	int	fd_in;

	if (cmd2->new_token[0] == '\0')
	{
		ft_putstr_fd("No EOF keyword (cmd << EOF_keyword)\n", 2);
		return ;
	}
	create_file(".heredoc", cmd2->new_token);
	fd_in = open(".heredoc", O_RDONLY);
	if (fd_in < 0)
		unlink(".heredoc");
	if (cmd1->new_token[0] != '\0')
		ft_dup_redir_in(cmd1, fd_in, copy);
	close(fd_in);
	unlink(".heredoc");
}
