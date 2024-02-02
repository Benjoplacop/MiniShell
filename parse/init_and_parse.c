/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:31:30 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/10 20:32:30 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_token2(t_token *token, char *str, int *i, int *t)
{
	int	j;

	j = *i;
	if (str[*i + 1] && (str[*i] == str[*i + 1]) && str[*i] != ')')
	{
		token[(*t)++].token = ft_substr(str, j, 2);
		*i = *i + 1;
	}
	else
		token[(*t)++].token = ft_substr(str, j, 1);
	if (str[*i + 1] == ' ' || str[*i + 1] == '\t')
		*i = *i + 1;
	*i = *i + 1;
}

static void	fill_token3(t_token *token, char *str, int *i, int *t)
{
	int	j;
	int	quote;

	j = *i;
	quote = str[j];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	token[(*t)++].token = ft_substr(str, j, *i - j + 1);
	if (str[*i] == '\0')
		return ;
	(*i)++;
}

void	fill_token(t_token *token, char *str)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	t = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		j = i;
		if (str[i] && ft_strchr("<>()|& ", str[i]))
			fill_token2(token, str, &i, &t);
		else if (str[i] && (str[i] == '\'' || str[i] == '"'))
			fill_token3(token, str, &i, &t);
		else
		{
			while (str[i] && ft_strchr("\'\"<>()|& ", str[i]) == NULL)
				i++;
			token[t++].token = ft_substr(str, j, i - j);
		}
	}
}

/*void	ft_print(t_cmd *cmd)
{
	int	i = 0;
	while (i < count_token(cmd->new_token))
	{
		if (cmd->new_tok == NULL)
		{
			ft_putstr_fd(cmd->new_token, 2);
			ft_putstr_fd("\n", 2);
			return;
		}
		else
		{
			ft_putstr_fd(cmd->new_token, 2);
			ft_putstr_fd("\n", 2);
			ft_print(cmd->new_tok->cmd);
			if(cmd->new_tok->next->next->new_token != NULL)
			{
				ft_putstr_fd(cmd->new_tok->next->next->new_token, 2);
				ft_putstr_fd("\n", 2);
				ft_print(cmd->new_tok->next->next->cmd);
				return ;
			}
		}
	}
}
*/
int	init_and_parse(char *line, t_copy *copy)
{
	if (check_quote(line) == -1 || check_pipe(line, -1) == -1)
		return (write(2, "Syntax error\n", 13));
	copy->cmd = malloc(sizeof(t_cmd));
	copy->line = line;
	copy->cmd->new_token = line;
	copy->cmd->tok = malloc(sizeof(t_token) * count_token(line));
	copy->cmd->new_tok = NULL;
	copy->cmd->env = get_dup_env(copy->envp);
	fill_token(copy->cmd->tok, line);
	type_token(copy->cmd);
	separe_token(copy->cmd);
	exec_cmd(copy->cmd, copy);
	free_cmd(copy->cmd);
	free(copy->cmd->tok);
	free(copy->cmd);
	return (1);
}
