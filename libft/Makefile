# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbilly <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 12:24:32 by mbilly            #+#    #+#              #
#    Updated: 2023/02/16 14:38:28 by mbilly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =  ft_strjoin.c ft_isalnum.c ft_itoa.c \
	ft_strlcpy.c ft_isprint.c ft_strmapi.c \
	ft_isascii.c ft_strnstr.c ft_isalpha.c \
	ft_strrchr.c ft_putstr_fd.c ft_split.c \
	ft_isdigit.c ft_memset.c ft_memchr.c \
	ft_strchr.c ft_calloc.c ft_memmove.c \
	ft_substr.c ft_memcpy.c ft_putchar_fd.c \
	ft_bzero.c ft_toupper.c ft_strtrim.c\
	ft_tolower.c ft_strlcat.c ft_striteri.c \
	ft_memcmp.c ft_putendl_fd.c ft_strdup.c \
	ft_atoi.c ft_strlen.c ft_strncmp.c \
	ft_putnbr_fd.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstmap.c ft_lstiter.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus :		$(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean : 
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all
