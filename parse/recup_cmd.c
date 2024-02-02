/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:07:52 by mbilly            #+#    #+#             */
/*   Updated: 2023/06/29 13:56:46 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	and_funct(t_cmd *cmd)
{
	if (g_ft_error == 0)
	{
		take_line(cmd->new_token, cmd->env);
		ft_putstr_fd("g_error = 0\n", 1);
	}
	else
	{
		ft_putstr_fd("g_error = -1\n", 1);
		return (-1);
	}
	return (0);
}

static void	ft_exec_cmd(t_cmd *cmd, char *sep)
{
	static int	used_sep;

	if (used_sep == 0)
	{
		if (sep == NULL)
		{
			take_line(cmd->new_token, cmd->env);
			return ;
		}
		if (ft_strncmp(sep, "&&", 2) == 0)
			if (and_funct(cmd) == -1)
				return ;
		used_sep++;
	}
	else
	{
		if (ft_strncmp(sep, "&&", 2) == 0)
			if (and_funct(cmd) == -1)
				return ;
		used_sep--;
	}
}

void	recup_cmd(t_cmd *cmd, char *sep)
{
	int	i;

	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (cmd->new_tok == NULL)
		{
			ft_exec_cmd(cmd, sep);
			return ;
		}
		else
		{
			recup_cmd(cmd->new_tok->cmd, cmd->new_tok->next->new_token);
			if (cmd->new_tok->next->next->new_token != NULL)
			{
				recup_cmd(cmd->new_tok->next->next->cmd,
					cmd->new_tok->next->new_token);
				return ;
			}
			else
				return ;
		}
	}
}
