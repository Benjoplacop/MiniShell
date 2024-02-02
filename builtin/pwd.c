/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:40:13 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/01 03:30:53 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd(void)
{
	char	cwd[1024];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	pwd = ft_strdup(cwd);
	return (pwd);
}

void	print_pwd(void)
{
	char	*printed_pwd;

	printed_pwd = pwd();
	ft_putstr_fd(printed_pwd, 1);
	ft_putstr_fd("\n", 1);
	free(printed_pwd);
}
