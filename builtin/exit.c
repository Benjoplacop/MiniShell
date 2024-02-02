/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:50:54 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/07 16:29:39 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_clean(char *line, t_copy *copy)
{
	free_split(copy->envp);
	free_tok(copy->cmd->tok, copy->line);
	free(copy->cmd->tok);
	free_split(copy->cmd->env);
	free(copy->cmd);
	free(line);
	free(copy);
	exit(1);
}
