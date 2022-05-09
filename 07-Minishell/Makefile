# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 18:16:46 by ebassi            #+#    #+#              #
#    Updated: 2022/04/04 17:31:51 by dripanuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCSFLS = main.c
HEADER = minishell.h
FLAGS = gcc -lreadline -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

all: minishell

$(LIBFT):
	$(MAKE) -C ./libft

minishell: $(LIBFT)
	$(FLAGS) $(LIBFT) $(SRCSFLS) -o minishell

clean:
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f minishell
	$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re bonus