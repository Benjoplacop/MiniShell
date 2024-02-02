/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:02:26 by mbilly            #+#    #+#             */
/*   Updated: 2023/08/12 12:26:33 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*group_echo(t_copy *copy)
{
	int		i;
	char	*res;

	res = NULL;
	i = -1;
	while (++i < count_token(copy->line) && \
			ft_strncmp(copy->cmd->tok[i].token, "echo", 4) != 0)
		i++;
	while (i < count_token(copy->line) && \
			ft_strncmp(copy->cmd->tok[i].token, "|", 1) != 0 && \
			ft_strncmp(copy->cmd->tok[i].token, ">>", 2) != 0 && \
			ft_strncmp(copy->cmd->tok[i].token, "<<", 2) != 0 && \
			ft_strncmp(copy->cmd->tok[i].token, "<", 1) != 0 && \
			ft_strncmp(copy->cmd->tok[i].token, ">", 1) != 0 && \
			ft_strncmp(copy->cmd->tok[i].token, "&&", 1) != 0)
	{
		if (res == NULL)
			res = ft_strdup(copy->cmd->tok[i].token);
		else
			res = ft_realloc(res, copy->cmd->tok[i].token);
		i++;
	}
	return (res);
}
