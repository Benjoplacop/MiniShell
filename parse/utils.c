/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:02:09 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/10 21:15:24 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tok(t_token *tok, char *new_token)
{
	int	i;

	i = count_token(new_token);
	while (--i >= 0)
		free(tok[i].token);
}

void	free_new_tok(t_new_token *new_tok)
{
	if (new_tok == NULL)
	{
		free(new_tok);
		return ;
	}
	free(new_tok->next->next->cmd->new_token);
	free(new_tok->next->next->new_token);
	free(new_tok->next->next->cmd->tok);
	free(new_tok->next->next->cmd);
	free(new_tok->next->next);
	free(new_tok->next->new_token);
	free(new_tok->next);
	free(new_tok->cmd->new_token);
	free(new_tok->cmd->tok);
	free(new_tok->cmd);
	free(new_tok->new_token);
	free(new_tok);
}

void	free_split(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free);
}

void	free_maillon(t_cmd *cmd)
{
	free_split(cmd->env);
	free_tok(cmd->tok, cmd->new_token);
	free_new_tok(cmd->new_tok);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (cmd->new_tok == NULL)
		{
			free_maillon(cmd);
			return ;
		}
		else
		{
			free_cmd(cmd->new_tok->cmd);
			if (cmd->new_tok->next->next->new_token != NULL)
				free_cmd(cmd->new_tok->next->next->cmd);
			free_maillon(cmd);
			return ;
		}
	}
}
