/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:39:45 by bhennequ          #+#    #+#             */
/*   Updated: 2023/10/03 13:01:03 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_arg(char *line)
{
	int	i;

	i = 5;
	if (line[i] == '-')
	{
		while ((line[i] == 'n' && (line[i - 1] == 'n' || line[i - 1] == '-')
				&& (line[i + 1] == ' ' || line[i + 1] == 'n'
					|| line[i + 1] == '-')) || line[i] == ' '
			|| (line[i] == '-' && only_n(line, i) != 0))
			i++;
	}
	else
		return (0);
	return (i);
}

static void	echo_s_quote(char *line, char quote, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		ft_putchar_fd(line[*i], 1);
		(*i)++;
	}
	(*i)++;
}

static char	*echo_d_quote(char *line, int *i, char **envp, int *bool_free)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '$')
		{
			line = replace_var_env(&line[*i], envp);
			*i = 0;
			(*bool_free)++;
		}
		ft_putchar_fd(line[*i], 1);
		(*i)++;
	}
	(*i)++;
	return (line);
}

static void	echo2(char *line, int *i, char **envp)
{
	int	bool_free;

	bool_free = 0;
	while (line[*i])
	{
		if (line[*i] == '\'')
			echo_s_quote(line, line[*i], i);
		else if (line[*i] == '"')
			line = echo_d_quote(line, i, envp, &bool_free);
		else
		{
			ft_putchar_fd(line[*i], 1);
			(*i)++;
		}
	}
	if (bool_free > 0)
		free(line);
}

void	echo(char *line, char **envp)
{
	int		i;
	int		ret;

	i = 5;
	if (ft_strncmp("echo\0", line, 5) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	ret = echo_arg(line);
	if (ret == 0)
		i = 5;
	else
		i = ret;
	echo2(line, &i, envp);
	if (!ret)
		write(1, "\n", 1);
	g_ft_error = 0;
}
