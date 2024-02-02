/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separe_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:29:01 by mbilly            #+#    #+#             */
/*   Updated: 2023/08/16 14:23:45 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_token_fill(t_cmd *cmd, char *sep)
{
	cmd->new_tok = create_first_new_token(cmd, cmd->tmp_cmd,
			sep, cmd->tmp_cmd_next);
	if (cmd->tmp_cmd != NULL)
	{
		fill_token(cmd->new_tok->cmd->tok, cmd->tmp_cmd);
		type_token(cmd->new_tok->cmd);
	}
	if (cmd->tmp_cmd_next != NULL)
	{
		fill_token(cmd->new_tok->next->next->cmd->tok, cmd->tmp_cmd_next);
		type_token(cmd->new_tok->next->next->cmd);
	}
}

int	join_and_token(t_cmd *cmd, char *sep, int j, int i)
{
	if (cmd->tmp_cmd == NULL)
		cmd->tmp_cmd_next = ft_strdup(cmd->tok[j].token);
	else
	{
		while (j < i)
		{
			cmd->tmp_cmd = ft_strjoin2(cmd->tmp_cmd, " ");
			cmd->tmp_cmd = ft_strjoin2(cmd->tmp_cmd, cmd->tok[j].token);
			j++;
		}
	}
	i++;
	if (cmd->tmp_cmd_next == NULL)
		if (i < count_token(cmd->new_token))
			cmd->tmp_cmd_next = ft_strdup(cmd->tok[i].token);
	i++;
	while (i < count_token(cmd->new_token))
	{
		cmd->tmp_cmd_next = ft_strjoin2(cmd->tmp_cmd_next, " ");
		cmd->tmp_cmd_next = ft_strjoin2(cmd->tmp_cmd_next, cmd->tok[i].token);
		i++;
	}
	join_token_fill(cmd, sep);
	return (i);
}

void	check_free(t_cmd *cmd, char *sep)
{
	if (sep != NULL)
		free(sep);
	if (cmd->tmp_cmd != NULL)
		free(cmd->tmp_cmd);
	if (cmd->tmp_cmd_next != NULL)
		free(cmd->tmp_cmd_next);
}

int	separe_and(t_cmd *cmd, int j, int i)
{
	char	*sep;

	sep = NULL;
	cmd->tmp_cmd = NULL;
	cmd->tmp_cmd_next = NULL;
	if (cmd->tok[i].level == 0 && \
			(ft_strncmp(cmd->tok[i].token, "&&", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, "||", 2) == 0))
	{
		sep = ft_strdup(cmd->tok[i].token);
		cmd->tmp_cmd = ft_strdup(cmd->tok[j].token);
		j++;
		i = join_and_token(cmd, sep, j, i);
	}
	check_free(cmd, sep);
	return (i);
}

int	separe_redir(t_cmd *cmd, int j, int i)
{
	char	*sep;

	sep = NULL;
	cmd->tmp_cmd = NULL;
	cmd->tmp_cmd_next = NULL;
	if (cmd->tok[i].level == 0 && \
			(ft_strncmp(cmd->tok[i].token, "<<", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, "<", 1) == 0 || \
			ft_strncmp(cmd->tok[i].token, ">>", 2) == 0 || \
			ft_strncmp(cmd->tok[i].token, ">", 1) == 0))
	{
		sep = check_before_separe_pipe(cmd, j, &i);
	}
	check_free(cmd, sep);
	return (i);
}
