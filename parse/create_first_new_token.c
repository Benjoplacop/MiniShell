/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_first_new_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:45:15 by mbilly            #+#    #+#             */
/*   Updated: 2023/07/06 16:10:31 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_token2(t_new_token *new, char *sep,
		char *cmd_next, t_cmd *st_cmd)
{
	new->next->new_token = ft_strdup(sep);
	new->next->previous = new;
	new->next->next = malloc(sizeof(t_new_token));
	new->next->cmd = NULL;
	new->next->next->previous = new->next;
	new->next->next->next = NULL;
	new->next->next->cmd = malloc(sizeof(t_cmd));
	if (cmd_next != NULL)
	{
		new->next->next->cmd->new_token = ft_strdup(cmd_next);
		new->next->next->new_token = ft_strdup(cmd_next);
		new->next->next->cmd->tok = malloc(sizeof(t_token)
				* count_token(cmd_next));
		new->next->next->cmd->new_tok = NULL;
		new->next->next->cmd->env = get_dup_env(st_cmd->env);
	}
	else
	{
		new->next->next->new_token = ft_strdup("\0");
		new->next->next->cmd->new_token = ft_strdup("\0");
		new->next->next->cmd->tok = malloc(sizeof(t_token));
		new->next->next->cmd->env = NULL;
	}
}

t_new_token	*create_first_new_token(t_cmd *st_cmd, char *cmd,
		char *sep, char *cmd_next)
{
	t_new_token	*new;

	new = malloc(sizeof(t_new_token));
	new->previous = NULL;
	new->next = malloc(sizeof(t_new_token));
	new->cmd = malloc(sizeof(t_cmd));
	if (cmd != NULL)
	{
		new->new_token = ft_strdup(cmd);
		new->cmd->new_token = ft_strdup(cmd);
		new->cmd->tok = malloc(sizeof(t_token) * count_token(cmd));
		new->cmd->new_tok = NULL;
		new->cmd->env = get_dup_env(st_cmd->env);
	}
	else
	{
		new->new_token = ft_strdup("\0");
		new->cmd->new_token = ft_strdup("\0");
		new->cmd->tok = malloc(sizeof(t_token) * 1);
		new->cmd->env = NULL;
	}
	create_new_token2(new, sep, cmd_next, st_cmd);
	return (new);
}
