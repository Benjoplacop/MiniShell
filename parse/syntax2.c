/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:02:19 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/16 14:04:50 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parenthesis(char *str)
{
	int	i;
	int	o_parenth;
	int	c_parenth;

	o_parenth = 0;
	c_parenth = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			o_parenth++;
		else if (str[i] == ')')
			c_parenth++;
		if (i == inside_quote(str, i))
			i++;
		else
			i = inside_quote(str, i);
		if (i == (int)ft_strlen(str))
			break ;
	}
	if (o_parenth == c_parenth)
		return (0);
	return (-1);
}

int	check_quote(char *str)
{
	int	i;
	int	inside;
	int	s_count;
	int	d_count;

	i = -1;
	inside = 0;
	s_count = 0;
	d_count = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			s_count += check_quote_utils(&str[i], &inside, '\'');
		else if (str[i] == '"')
			d_count += check_quote_utils(&str[i], &inside, '"');
	}
	if (s_count % 2 == 1 || d_count % 2 == 1)
		return (-1);
	return (0);
}

int	check_after_last_pipe(char *str, int i)
{
	i--;
	if (str[i] && str[i] == '|')
		return (-1);
	if (check_redir(str, '<') == -1 || check_redir(str, '>') == -1)
		return (-1);
	if (check_and(str) == -1)
		return (-1);
	if (check_parenthesis(str) == -1)
		return (-1);
	return (0);
}

int	check_sep(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (D_LEFT_REDIR);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (S_LEFT_REDIR);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (D_RIGHT_REDIR);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (S_RIGHT_REDIR);
	return (0);
}

void	separe_token_three(t_cmd *cmd, int j)
{
	int	i;

	i = -1;
	while (++i < count_token(cmd->new_token))
	{
		if (separe_redir(cmd, j, i) >= count_token(cmd->new_token))
		{
			if (cmd->new_tok->cmd->new_token != NULL)
				separe_token(cmd->new_tok->cmd);
			if (cmd->new_tok->next->next->cmd->new_token != NULL)
				separe_token(cmd->new_tok->next->next->cmd);
			return ;
		}
	}
}
