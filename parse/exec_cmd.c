/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:54:25 by mbilly            #+#    #+#             */
/*   Updated: 2023/08/14 16:17:57 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_simple(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (check_sep(cmd->tok[i].token) != 0
			|| (ft_strncmp(cmd->tok[i].token, "||", 2) != 0 && \
					ft_strncmp(cmd->tok[i].token, "|", 1) == 0))
			return (1);
	}
	return (0);
}

static void	exec_multiple_cmd_two(t_cmd *cmd1, char *sep, t_cmd *cmd2,
		t_copy *copy)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (ft_strncmp(sep, "||", 2) == 0)
	{
		exec_cmd(cmd1, copy);
		if (g_ft_error != 0)
			exec_cmd(cmd2, copy);
		else
		{
			tmp = skip_or(cmd2);
			if (tmp == NULL)
				return ;
		}
	}
	if (tmp != NULL)
		exec_cmd(tmp->new_tok->next->next->cmd, copy);
	if (ft_strncmp(sep, "|", 1) == 0 && ft_strncmp(sep, "||", 2) != 0)
		ft_pipe(cmd1, cmd2, copy);
	if (check_sep(sep) == D_RIGHT_REDIR || check_sep(sep) == D_LEFT_REDIR
		|| check_sep(sep) == S_RIGHT_REDIR || check_sep(sep) == S_LEFT_REDIR)
		redir(cmd1, sep, cmd2, copy);
}

static void	exec_multiple_cmd(t_cmd *cmd1, char *sep, t_cmd *cmd2, t_copy *copy)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (ft_strncmp(sep, "&&", 2) == 0)
	{
		exec_cmd(cmd1, copy);
		if (g_ft_error != 0)
		{
			tmp = skip_and(cmd2);
			if (tmp == NULL)
				return ;
		}
		exec_cmd(cmd2, copy);
		if (g_ft_error != 0)
		{
			tmp = skip_and(cmd2);
			if (tmp == NULL)
				return ;
		}
	}
	if (tmp != NULL)
		exec_cmd(tmp->new_tok->next->next->cmd, copy);
	exec_multiple_cmd_two(cmd1, sep, cmd2, copy);
}

void	exec_cmd(t_cmd *cmd, t_copy *copy)
{
	t_cmd	*tmp;

	if (ft_strncmp(cmd->tok[0].token, "(", 1) == 0 && \
		ft_strncmp(cmd->tok[count_token(cmd->new_token) - 1].token,
			")", 1) == 0)
	{
		tmp = cmd->new_tok->cmd;
		if (is_simple(tmp) == 0)
			take_line(tmp->new_token, copy);
		else
			exec_multiple_cmd(tmp->new_tok->cmd, tmp->new_tok->next->new_token,
				tmp->new_tok->next->next->cmd, copy);
		return ;
	}
	if (is_simple(cmd) == 0)
		take_line(cmd->new_token, copy);
	else
		exec_multiple_cmd(cmd->new_tok->cmd, cmd->new_tok->next->new_token,
			cmd->new_tok->next->next->cmd, copy);
}
