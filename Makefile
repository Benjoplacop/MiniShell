NAME = minishell

LIBFT = ./libft/libft.a

SRCS = utils/main.c utils/var_env.c utils/utils.c utils/get_next_line_bonus.c utils/ft_strjoin2.c builtin/run_program.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c \
       parse/syntax2.c builtin/export.c builtin/pwd.c builtin/unset.c parse/group_cmd.c parse/init_and_parse.c parse/exec_cmd.c \
       parse/separe_token.c parse/syntax.c parse/utils.c pipe_redir/redir.c pipe_redir/d_redir.c pipe_redir/s_redir.c pipe_redir/pipe.c \
	   parse/utils2.c utils_main.c parse/create_first_new_token.c parse/type_token.c parse/count_token.c parse/skip.c parse/separe_token2.c \
	   pipe_redir/redir2.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):	$(OBJS)
	gcc $(SRCS) $(LIBFT) $(CFLAGS) -g -o $(NAME) -lreadline

clean:
	@rm -f *.o
	@rm -f parse/*.o
	@rm -f builtin/*.o
	@rm -f pipe_redir/*.o

fclean:	clean
	@rm -rf $(NAME)

re:	fclean all
