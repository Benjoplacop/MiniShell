/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separe_token2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:26:46 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/16 14:26:22 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	separe_parenth(t_cmd *cmd, int i)
{
	cmd->tmp_cmd = NULL;
	if (cmd->tok[i].level == 1 && \
			ft_strncmp(cmd->tok[i].token, "(", 1) == 0)
	{
		i++;
		cmd->tmp_cmd = ft_strdup(cmd->tok[i++].token);
		while (i < count_token(cmd->new_token) && \
				(cmd->tok[i].level >= 1 || \
				ft_strncmp(cmd->tok[i].token, ")", 1) != 0))
		{
			cmd->tmp_cmd = ft_strjoin2(cmd->tmp_cmd, " ");
			cmd->tmp_cmd = ft_strjoin2(cmd->tmp_cmd, cmd->tok[i].token);
			i++;
		}
		i++;
		cmd->new_tok = create_first_new_token(cmd, cmd->tmp_cmd, "(", NULL);
		fill_token(cmd->new_tok->cmd->tok, cmd->tmp_cmd);
		type_token(cmd->new_tok->cmd);
	}
	if (cmd->tmp_cmd != NULL)
		free(cmd->tmp_cmd);
	return (i);
}

char	*check_before_separe_pipe(t_cmd *cmd, int j, int *i)
{
	char	*sep;

	sep = NULL;
	if (ft_strncmp(cmd->tok[*i].token, cmd->tok[j].token,
			ft_strlen(cmd->tok[j].token)) == 0)
	{
		sep = ft_strdup(cmd->tok[*i].token);
		j++;
		*i = join_and_token(cmd, sep, j, *i);
	}
	else
	{
		sep = ft_strdup(cmd->tok[*i].token);
		cmd->tmp_cmd = ft_strdup(cmd->tok[j].token);
		j++;
		*i = join_and_token(cmd, sep, j, *i);
	}
	return (sep);
}

int	separe_pipe(t_cmd *cmd, int j, int i)
{
	char	*sep;

	sep = NULL;
	cmd->tmp_cmd = NULL;
	cmd->tmp_cmd_next = NULL;
	if (cmd->tok[i].level == 0 && \
			ft_strncmp(cmd->tok[i].token, "|", 1) == 0)
	{
		sep = check_before_separe_pipe(cmd, j, &i);
	}
	check_free(cmd, sep);
	return (i);
}

void	separe_token(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < count_token(cmd->new_token))
	{
		if (separe_and(cmd, j, i) >= count_token(cmd->new_token))
		{
			separe_token(cmd->new_tok->cmd);
			separe_token(cmd->new_tok->next->next->cmd);
			return ;
		}
	}
	separe_token_two(cmd, j);
}

void	separe_token_two(t_cmd *cmd, int j)
{
	int	i;

	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (separe_pipe(cmd, j, i) >= count_token(cmd->new_token))
		{
			if (cmd->new_tok->cmd->new_token != NULL)
				separe_token(cmd->new_tok->cmd);
			if (cmd->new_tok->next->next->cmd->new_token != NULL)
				separe_token(cmd->new_tok->next->next->cmd);
			return ;
		}
	}
	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (separe_parenth(cmd, i) >= count_token(cmd->new_token))
		{
			separe_token(cmd->new_tok->cmd);
			return ;
		}
	}
	separe_token_three(cmd, j);
}
