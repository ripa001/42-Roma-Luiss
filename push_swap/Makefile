# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/05 12:22:32 by mabasset          #+#    #+#              #
#    Updated: 2022/03/18 17:28:02 by dripanuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
SRC = checker.c main.c swap.c push.c rotate.c rev_rotate.c utility.c utility2.c findcomb.c count_moves.c move.c utils_movement.c sort_5.c sort_5_utils.c
SRC_BONUS = bonus/checker.c bonus/checker_2.c bonus/checker_3.c
SRC_UTILS = checker.c push.c swap.c rotate.c count_moves.c utility.c rev_rotate.c utils_movement.c move.c
GNL = gnl/get_next_line_utils.c gnl/get_next_line.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -g
LIBFT = ./libft/libft.a

CC = gcc
FLAGS = -Wall -Werror -Wextra

all: push_swap checker

bonus: push_swap checker

$(LIBFT):
	$(MAKE) -C ./libft

push_swap: $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) -o push_swap

checker: $(LIBFT)
	$(CC) $(FLAGS) $(SRC_UTILS) $(SRC_BONUS) $(GNL) $(LIBFT) -o checker

clean:
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f push_swap checker
	$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re bonus