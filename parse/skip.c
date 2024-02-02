/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:31:30 by mbilly            #+#    #+#             */
/*   Updated: 2023/08/12 12:30:18 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*skip_and(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd->new_tok == NULL)
		return (NULL);
	else
	{
		tmp = cmd;
		if (ft_strncmp(tmp->new_tok->next->new_token, "&&", 2) == 0)
		{
			tmp = tmp->new_tok->next->next->cmd;
			if (skip_and(tmp) == NULL)
				return (NULL);
		}
		else if (ft_strncmp(tmp->new_tok->next->new_token, "||", 2) == 0)
			return (tmp);
	}
	return (NULL);
}

t_cmd	*skip_or(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd->new_tok == NULL)
		return (NULL);
	else
	{
		tmp = cmd;
		if (ft_strncmp(tmp->new_tok->next->new_token, "||", 2) == 0)
		{
			tmp = tmp->new_tok->next->next->cmd;
			if (skip_or(tmp) == NULL)
				return (NULL);
		}
		else if (ft_strncmp(tmp->new_tok->next->new_token, "&&", 0) == 0)
			return (tmp);
	}
	return (NULL);
}
