/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:12:18 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/03 15:16:15 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ft_error;

void	take_new_line(char *line, t_copy *copy)
{
	if (ft_strncmp(line, "exit", 4) == 0)
		exit_clean(line, copy);
	else if (ft_strncmp("unset", line, 5) == 0)
		copy->envp = unset_var(line + 5, copy->envp);
	else if (ft_strncmp("cd", line, 2) == 0)
		copy->envp = cd(line + 3, copy->envp);
	else if (ft_strncmp("export", line, 6) == 0)
		copy->envp = export_var(line, copy->envp);
	else if (ft_strncmp(".", line, 1) == 0 || ft_strncmp("/", line, 1) == 0)
		run_program(ft_split(line, ' '), copy->envp);
	else if (ft_strncmp("echo ", line, 5) == 0)
		echo(line, copy->envp);
	else if (take_path("PATH", copy->envp) == 0)
		take_and_run_path(take_var_env("PATH", copy->envp),
			ft_split(line, ' '), copy->envp);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		print_pwd();
	else if (ft_strncmp(line, "env", 3) == 0)
		env(copy->envp);
	free(line);
}

void	take_line2(char *line, t_copy *copy)
{
	if (ft_strncmp(line, "exit", 4) == 0)
		exit_clean(line, copy);
	else if (ft_strncmp("unset", line, 5) == 0)
		copy->envp = unset_var(line + 5, copy->envp);
	else if (ft_strncmp("cd", line, 2) == 0)
		copy->envp = cd(line, copy->envp);
	else if (ft_strncmp("export", line, 6) == 0)
		copy->envp = export_var(line, copy->envp);
	else if (ft_strncmp(".", line, 1) == 0 || ft_strncmp("/", line, 1) == 0)
		run_program(ft_split(line, ' '), copy->envp);
	else if (ft_strncmp("echo ", line, 5) == 0)
		echo(line, copy->envp);
	else if (take_path("PATH", copy->envp) == 0)
		take_and_run_path(take_var_env("PATH", copy->envp),
			ft_split(line, ' '), copy->envp);
	else if (ft_strncmp(line, "pwd", 3) == 0)
		print_pwd();
	else if (ft_strncmp(line, "env", 3) == 0)
		env(copy->envp);
}

char	*get_new_line(char *line, t_copy *copy)
{
	char	*tmp;
	char	*res;

	if (dollar_is_here(line) == 1)
	{
		res = ft_strdup(line);
		while (dollar_is_here(res) == 1)
		{
			tmp = ft_strdup(res);
			free(res);
			res = replace_var_env(tmp, copy->envp);
			free(tmp);
		}
		return (res);
	}
	return (NULL);
}

void	take_line(char *line, t_copy *copy)
{
	char	*new_line;

	new_line = get_new_line(line, copy);
	if (new_line == NULL)
	{
		free(new_line);
		take_line2(line, copy);
	}
	else
		take_new_line(new_line, copy);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_copy				*copy;

	(void)argc;
	(void)argv;
	g_ft_error = 0;
	copy = malloc(sizeof(t_copy));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	copy->envp = get_dup_env(envp);
	copy->envp = minishell_test(copy->envp);
	take_line("clear", copy);
	prompt(copy);
}
