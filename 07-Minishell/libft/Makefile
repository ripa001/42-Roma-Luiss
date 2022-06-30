# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 16:02:33 by mpatrini          #+#    #+#              #
#    Updated: 2022/06/04 01:22:30 by mpatrini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc
LIBC	= ar rc
CFLAGS	+= -Wall -Werror -Wextra -c
SRC = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_memchr.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c \
		ft_printf_utility.c \
		ft_printf_utility2.c \
		ft_printf_other.c \
		ft_printf_other2.c \
		ft_printf_other3.c \
		ft_printf_fun.c \
		ft_printf_fun2.c \
		ft_printf_fun3.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_atoi_long.c \
		ft_exit_error.c \
		ft_strlen_matrix.c \
		ft_strcmp.c \
		ft_free_matrix.c \
		ft_abs.c \
		ft_free_lst.c \

OBJS	= $(SRC:.c=.o)

NAME	= libft.a

.PHONY: all clean fclean re

%o :	%c
	@${CC} ${CFLAGS} -c $< -o $@
	
$(NAME): ${OBJS}
	@printf "\e[92mBuilding Libft...\e[39m\n"
	@ar -rc ${NAME} ${OBJS}
	@ranlib ${NAME}

all: $(NAME)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f *~ $(NAME)

re: fclean all

