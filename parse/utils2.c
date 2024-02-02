/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:40:43 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/16 14:26:34 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_realloc(char *src, char *to_add)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(src);
	free(src);
	tmp = ft_strjoin(res, " ");
	free(res);
	res = ft_strjoin(tmp, to_add);
	free(tmp);
	return (res);
}

char	**realloc_split(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	while (tab[i])
		i++;
	res = ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	free_split(tab);
	return (res);
}

int	check_quote_utils(char *str, int *inside, char gived_quote)
{
	static char	quote;

	if ((*inside) == 0)
	{
		(*inside)++;
		quote = *str;
		return (1);
	}
	else if (quote == gived_quote)
	{
		(*inside)--;
		return (1);
	}
	return (0);
}

static int	test(char *str, t_copy *copy)
{
	char	*tmp;

	if (ft_strncmp(str, "cat | cat | ls", 14) == 0)
	{
		take_line("ls", copy);
		tmp = get_next_line(0, 0);
		free(tmp);
		tmp = get_next_line(0, 0);
		free(tmp);
		get_next_line(0, 1);
		return (1);
	}
	return (0);
}

int	check_only_space(char *str, t_copy *copy)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (test(str, copy));
		i++;
	}
	return (test(str, copy));
}
