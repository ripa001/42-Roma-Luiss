# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# ${NAME}: $(OBJ)
# 	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# all: gcc so_long.c errors.c gnl/*.c libft/*.c srcs/*.c -Lmlx -lmlx -framework OpenGL -framework AppKit -Werror -Wextra -Wall -g -o so_long && ./so_long map.ber

NAME = so_long
SRC = my_lib/gnl/*.c my_lib/libft/*.c srcs/*.c

FLAGS = -Wall -Werror -Wextra -g -o
CC = gcc
OBJ = $(SRC:.=.o)

$(NAME):
	$(CC) $(FLAGS) $(SRCS)

all: $(NAME) | ./a.out map.ber

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) a.out

re: fclean all

