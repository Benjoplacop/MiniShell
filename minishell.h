/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:42:17 by mbilly            #+#    #+#             */
/*   Updated: 2023/10/10 19:35:10 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define BUFFER_SIZE 1
# define COMMANDE 1
# define S_LEFT_REDIR 2
# define S_RIGHT_REDIR 3
# define D_LEFT_REDIR 4
# define D_RIGHT_REDIR 5
# define D_QUOTE 6
# define S_QUOTE 7
# define PIPE 8
# define AND 9
# define O_PARENTH 10
# define C_PARENTH 11
# define OR 12

extern int	g_ft_error;

typedef struct s_token
{
	int		type;
	int		level;
	char	*token;
}t_token;

typedef struct s_new_token
{
	char				*new_token;
	struct s_new_token	*next;
	struct s_new_token	*previous;
	struct s_cmd		*cmd;
}t_new_token;

typedef struct s_cmd
{
	char		**env;
	char		*new_token;
	char		*tmp_cmd;
	char		*tmp_cmd_next;
	t_token		*tok;
	t_new_token	*new_tok;
}t_cmd;

typedef struct s_copy
{
	char	**envp;
	char	*line;
	t_cmd	*cmd;
}t_copy;

int			take_path(char *arg, char **envp);
int			check_only_space(char *str, t_copy *copy);
int			check_quote_utils(char *str, int *inside, char gived_quote);
int			run_program(char **args, char **envp);
int			init_and_parse(char *line, t_copy *copy);
int			check_quote(char *str);
int			check_pipe(char *str, int i);
int			count_token(char *str);
int			check_sep(char *str);
int			nb_pipe(t_cmd *cmd);
int			check_after_last_pipe(char *str, int i);
int			check_quote(char *str);
int			inside_quote(char *str, int i);
int			check_redir(char *str, char c);
int			check_and(char *str);
int			check_parenthesis(char *str);
int			separe_pipe(t_cmd *cmd, int j, int i);
int			dollar_is_here(char *line);
int			skip_s_quote(char *line);
int			separe_redir(t_cmd *cmd, int j, int i);
int			separe_parenth(t_cmd *cmd, int i);
int			separe_and(t_cmd *cmd, int j, int i);
int			join_and_token(t_cmd *cmd, char *sep, int j, int i);
int			inside_quote(char *str, int i);
int			open_files_in_and_out(t_cmd *cmd2, char *sep, \
		int *fd_in, char *save);
int			only_n(char *line, int i);
void		close_all(int pipefd[], int fd_in, int fd_out);
void		create_file(char *fd, char *limiter);
void		join_token_fill(t_cmd *cmd, char *sep);
void		check_free(t_cmd *cmd, char *sep);
void		take_line(char *line, t_copy *copy);
int			take_and_run_path(char *path, char **command, char **envp);
void		separe_token(t_cmd *cmd);
void		prompt(t_copy *copy);
void		echo(char *line, char **envp);
void		add_to_lst_cmd(t_cmd *cmd, int start, int end, int child);
void		free_split(char **to_free);
void		type_token(t_cmd *cmd);
void		fill_token(t_token *token, char *str);
void		env(char **envp);
void		exec_cmd(t_cmd *cmd, t_copy *copy);
void		ft_pipe(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy);
void		redir(t_cmd *cmd1, char *sep, t_cmd *cmd2, t_copy *copy);
void		ft_dup_redir_in(t_cmd *cmd1, int fd_in, t_copy *copy);
void		ft_dup_redir_out(t_cmd *cmd1, int fd_in);
void		d_left_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy);
void		d_right_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy);
void		s_left_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy);
void		s_right_redir(t_cmd *cmd1, t_cmd *cmd2, t_copy *copy);
void		free_cmd(t_cmd *cmd);
void		free_tok(t_token *token, char *new_token);
void		exit_clean(char *line, t_copy *copy);
void		print_pwd(void);
void		free_maillon(t_cmd *cmd);
void		prompt(t_copy *copy);
void		signal_handler(int signum);
void		separe_token_two(t_cmd *cmd, int j);
void		separe_token_three(t_cmd *cmd, int j);
void		init_shell(char **envp);
void		free_fork(t_copy *copy);
void		free_new_tok(t_new_token *new_tok);
char		**unset_var(char *var_name, char **envp);
char		*get_next_line(int fd, int fin);
char		*ft_strjoin2(char *s1, const char *s2);
char		*ft_realloc(char *src, char *to_add);
char		**realloc_split(char **tab);
char		**cd(char *path, char **envp);
char		*pwd(void);
char		*check_before_separe_pipe(t_cmd *cmd, int j, int *i);
char		*group_echo(t_copy *copy);
char		**export_var(char *line, char **env);
char		**modif_env(char **env, int *j, int *i, char *line);
char		*copie_arg(char *envp, int len);
char		*take_var_env(char *arg, char **envp);
char		**get_dup_env(char **envp);
char		*replace_var_env(char *line, char **envp);
char		*command_existe(char **cmd, char **envp);
char		*take_last_redir(char *str, int i, char **sep, char to_find);
char		*take_last_redir_cond(char *str, int j, char **sep);
char		**minishell_test(char **envp);
t_cmd		*skip_and(t_cmd *cmd);
t_cmd		*skip_or(t_cmd *cmd);
t_new_token	*create_first_new_token(t_cmd *st_cmd, char *cmd, \
		char *sep, char *cmd_next);

#endif
