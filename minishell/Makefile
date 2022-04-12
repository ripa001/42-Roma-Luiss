# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 18:16:46 by ebassi            #+#    #+#              #
#    Updated: 2022/04/12 17:24:50 by ebassi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCSFLS = main.c utils.c
BUILTINS = cd.c echo.c pwd.c env.c exit.c export.c unset.c
SRCS = $(addprefix src/, $(SRCSFLS)) $(addprefix builtins/, $(BUILTINS))
HEADER = minishell.h
FLAGS = gcc -lreadline -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a

all: minishell

$(LIBFT):
	$(MAKE) -C ./libft

minishell: $(LIBFT)
	$(FLAGS) $(LIBFT) $(SRCS) -o minishell

clean:
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f minishell
	$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re bonus