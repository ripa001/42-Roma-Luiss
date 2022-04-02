NAME = philo
LIBFT = libft/libft.a
SRCS = init.c main.c thread.c utils_philo.c
OBJS = $(SRCS:.c=.o)
HEADER = philo.h
CC = gcc -pthread
FLAGS = -Wall -Werror -Wextra

all: philo

bonus: philo

philo:
	make -C libft
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean:	clean
	make fclean -C libft
	rm -f $(NAME)

play: all
	./$(NAME) 4 410 200 200

re:			fclean all

.PHONY:		all clean fclean re bonus