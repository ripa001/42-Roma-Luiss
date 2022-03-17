# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/05 12:22:32 by mabasset          #+#    #+#              #
#    Updated: 2022/03/12 00:04:22 by dripanuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
SRC = checker.c main.c swap.c push.c rotate.c rev_rotate.c utility.c utility2.c findcomb.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

$(NAME):
		make re -C libft
		gcc $(FLAG) -o $(NAME) $(SRC) $(LIBFT)

all:	$(NAME)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME) $(LIB)
		make fclean -C libft

re:		fclean all

.PHONY:	all clean fclean re