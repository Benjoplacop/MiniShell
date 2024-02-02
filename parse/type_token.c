/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:09:45 by mbilly            #+#    #+#             */
/*   Updated: 2023/07/04 16:10:56 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	type_token2(t_cmd *cmd, int i)
{
	if (ft_strncmp(cmd->tok[i].token, "echo", 4) == 0 || \
			ft_strncmp(cmd->tok[i].token, "pwd", 3) == 0 || \
			ft_strncmp(cmd->tok[i].token, "env", 3) == 0 || \
			ft_strncmp(cmd->tok[i].token, "unset", 5) == 0 || \
			ft_strncmp(cmd->tok[i].token, "take_arg", 8) == 0 || \
			ft_strncmp(cmd->tok[i].token, "cd", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, "ls", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, "export", 6) == 0 || \
			ft_strncmp(cmd->tok[i].token, "./", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, "exit", 5) == 0)
		cmd->tok[i].type = COMMANDE;
	else if (ft_strncmp(cmd->tok[i].token, ">>", 2) == 0)
		cmd->tok[i].type = D_RIGHT_REDIR;
	else if (ft_strncmp(cmd->tok[i].token, "<<", 2) == 0)
		cmd->tok[i].type = D_LEFT_REDIR;
	else if (ft_strncmp(cmd->tok[i].token, ">", 1) == 0)
		cmd->tok[i].type = S_RIGHT_REDIR;
	else if (ft_strncmp(cmd->tok[i].token, "<", 1) == 0)
		cmd->tok[i].type = S_LEFT_REDIR;
	else if (ft_strncmp(cmd->tok[i].token, "|", 1) == 0)
		cmd->tok[i].type = PIPE;
	else if (ft_strncmp(cmd->tok[i].token, "&&", 2) == 0)
		cmd->tok[i].type = AND;
}

void	type_token(t_cmd *cmd)
{
	int	level;
	int	i;

	i = -1;
	level = 0;
	while (++i < count_token(cmd->new_token))
	{
		type_token2(cmd, i);
		if (ft_strncmp(cmd->tok[i].token, "(", 1) == 0)
		{
			level++;
			cmd->tok[i].type = O_PARENTH;
		}
		else if (ft_strncmp(cmd->tok[i].token, ")", 1) == 0)
		{
			level--;
			cmd->tok[i].type = C_PARENTH;
		}
		cmd->tok[i].level = level;
	}
}
