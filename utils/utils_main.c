/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:55:35 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/18 15:59:27 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_s_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}

char	*replace_var_env2(char *line, int i, char **envp)
{
	int		j;
	char	*var;
	char	*new_line;

	i++;
	j = i;
	while (line[j] && line[j] != '$' && line[j] != ' '
		&& line[j] != '\t' && line[j] != '"' && line[j] != '\'')
		j++;
	new_line = ft_substr(line, i, j - i);
	if (ft_strncmp(new_line, "?", 1) == 0)
		var = ft_itoa(g_ft_error);
	else
		var = take_var_env(new_line, envp);
	free(new_line);
	new_line = ft_substr(line, 0, i - 1);
	new_line = ft_strjoin2(new_line, var);
	free(var);
	var = ft_substr(line, j, ((int)ft_strlen(line)) - j);
	new_line = ft_strjoin2(new_line, var);
	free(var);
	return (new_line);
}

char	*replace_var_env(char *line, char **envp)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
			i = i + skip_s_quote(&line[i]);
		if (line[i] == '$')
			return (replace_var_env2(line, i, envp));
		i++;
	}
	if (j == 0)
		return (line);
	return (new_line);
}

int	dollar_is_here(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = i + skip_s_quote(&line[i]);
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
