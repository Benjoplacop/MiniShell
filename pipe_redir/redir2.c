/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:29:43 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/10 19:36:19 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	while (str[i] && (str[i] == '"' || str[i] == '\''))
	{
		i++;
		while (str[i] && str[i] != quote)
		{
			if (str[i] && str[i] == '\\')
				i++;
			i++;
		}
		if (i == (int)ft_strlen(str))
			break ;
		else
			i++;
	}
	return (i);
}

char	*take_last_redir_cond(char *str, int j, char **sep)
{
	char	*tmp;
	char	*res;

	if (*sep != NULL)
		free(*sep);
	if (str[j - 1] == '>')
		*sep = ft_strdup(">>");
	else if (str[j - 1] == '<')
		*sep = ft_strdup("<<");
	else if (str[j] == '<')
		*sep = ft_strdup("<");
	else
		*sep = ft_strdup(">");
	j++;
	while (str[j] == ' ')
		j++;
	tmp = ft_strdup(&str[j]);
	j = 0;
	while (tmp[j] && tmp[j] != ' ')
		j++;
	res = ft_substr(tmp, 0, j);
	free(tmp);
	return (res);
}

char	*take_last_redir(char *str, int i, char **sep, char to_find)
{
	int		j;
	char	*res;

	res = NULL;
	j = ft_strlen(str) - 1;
	while (j >= i)
	{
		if (str[j] == to_find)
		{
			res = take_last_redir_cond(str, j, sep);
			return (res);
		}
		j--;
	}
	if (res == NULL)
	{
		j = 0;
		while (str[j] && str[j] != ' ')
			j++;
		res = ft_substr(str, 0, j);
	}
	return (res);
}

int	open_files_in_and_out(t_cmd *cmd2, char *sep, int *fd_in, char *save)
{
	int	fd_out;

	if (check_sep(sep) == S_LEFT_REDIR)
		*fd_in = open(cmd2->new_token, O_RDONLY);
	else
	{
		create_file(".heredoc", cmd2->new_token);
		*fd_in = open(".heredoc", O_RDONLY);
		if (*fd_in < 0)
			unlink(".heredoc");
	}
	cmd2->new_token = take_last_redir(save, 0, &sep, '>');
	if (check_sep(sep) == S_RIGHT_REDIR)
		fd_out = open(cmd2->new_token, O_CREAT | O_TRUNC | O_WRONLY, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd_out = open(cmd2->new_token, O_CREAT | O_APPEND | O_WRONLY, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd_out);
}

void	close_all(int pipefd[], int fd_in, int fd_out)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_in);
	close(fd_out);
}
