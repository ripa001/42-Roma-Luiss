# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 16:02:33 by mpatrini          #+#    #+#              #
#    Updated: 2022/06/29 20:52:45 by mpatrini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	./libft/libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g -I includes/ -I libft/

READLINE	= -L/usr/include -lreadline -lcurses -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

RM		=	rm -f

SRCSFLS = main.c \
			minishell.c \
			minishell2.c \
			minishell3.c \
			brackets.c \
			check_command.c \
			cmd_list.c \
			cmd_list2.c \
			env.c \
			exec.c \
			exec2.c \
			expand_env.c \
			expand_env2.c \
			get_command.c \
			heredoc-pipe.c \
			mini.c \
			redirections-fd.c \
			utility.c \
			quotes.c \
			wildcard.c \
			wildcard2.c \
			wildcard3.c \

BUILTINS = cd.c \
			pwd.c \
			env.c \
			exit.c \
			echo.c \
			export.c \
			export2.c \
			unset.c \

SRCS = $(addprefix src/, $(SRCSFLS)) $(addprefix builtins/, $(BUILTINS))

OBJ		=	$(SRCS:.c=.o)

$(NAME):	$(OBJ)
			@make -C libft/
			@printf "\e[92mBuilding $(NAME)...\e[39m\n"
			@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJ) $(READLINE)
			@printf "\e[102mEverything has been compiled, use './minishell' to run the program!\e[0m\n"

%.o	:	%.c
			@$(CC) $(CFLAGS) -c $< -o $@
				
all		:	$(NAME)

clean	:
			@printf "\e[93mCleaning Minishell objects...\e[39m\n"
			@$(RM) $(OBJ) $(OBJ2)
			@printf "\e[93mCleaning Libft objects...\e[39m\n"
			@make clean -C ./libft
			@printf "\e[103mAll objects have been deleted\e[0m\n"

fclean	:	clean
			@printf "\e[91mCleaning Minishell...\e[39m\n"
			@$(RM) $(NAME)
			@printf "\e[91mCleaning Libft...\e[39m\n"
			@make fclean -C ./libft
			@printf "\e[101mAll executables and libraries have been deleted\e[0m\n"

re		:	fclean all

test	:	all
			@./$(NAME)
			
leaks	:	all
			@leaks --atExit -- ./$(NAME)
			
l		:
			@leaks --atExit -- ./$(NAME)

norma	:
			@norminette

.PHONY	:	all clean fclean re test
