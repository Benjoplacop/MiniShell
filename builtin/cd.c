/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:41:31 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/26 17:50:15 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cd_null(char **envp)
{
	char	*tmp;
	char	*tmp2;
	char	*oldpwd;
	char	**envp_copy;

	oldpwd = take_var_env("PWD", envp);
	tmp = pwd();
	tmp2 = ft_strjoin("PWD=", tmp);
	free(tmp);
	envp = export_var(tmp2, envp);
	free(tmp2);
	tmp2 = ft_strjoin("OLDPWD=", oldpwd);
	envp_copy = export_var(tmp2, envp);
	free(tmp2);
	free(oldpwd);
	return (envp_copy);
}

char	*take_cd_null(char **envp)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("/nfs/homes/");
	tmp = take_var_env("USER", envp);
	str = ft_strjoin2(str, tmp);
	free(tmp);
	return (str);
}

char	**cd(char *path, char **envp)
{
	char	*tmp;

	if (ft_strncmp(path, "cd", 2) == 0
		&& (path[2] == '\0' || (path[2] == ' ' && path[3] == '\0')))
	{
		tmp = take_cd_null(envp);
		if (chdir(tmp) == -1)
		{
			g_ft_error = 1;
			perror("cd");
		}
		free(tmp);
	}
	else if (chdir(path + 3) == -1)
	{
		g_ft_error = 1;
		perror("cd");
	}
	else
		g_ft_error = 0;
	return (cd_null(envp));
}
