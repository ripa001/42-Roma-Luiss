SOURCES = .-..-.c
LIBFT = libft/*.c
NAME = push_swap
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -o

$(NAME):
	$(CC) $(SOURCES) $(LIBFT) $(FLAGS) $(NAME) -Llibft

all: libft $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

libft:
	make -C libft

re: fclean all

.PHONY: all clean fclean re