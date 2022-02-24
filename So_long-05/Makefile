NAME = so_long
SRC = so_long.c my_lib/gnl/*.c my_lib/libft/*.c \
	srcs/animation.c \
	srcs/check_map.c  \
	srcs/color.c \
	srcs/end_program.c \
	srcs/errors.c \
	srcs/imgs.c \
	srcs/map_set.c \
	srcs/move_enemy.c \
	srcs/move_enemy_sup.c \
	srcs/moves.c \
	srcs/moves_sup.c \
	srcs/rendering.c \
	srcs/so_long_sup.c \
	srcs/tilemap.c \
	srcs/tilemap_sup.c \
	srcs/validate.c

MIN = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Werror -Wextra -Wall -g -o
CC = gcc
OBJ = $(SRC:.=.o)

$(NAME):
	$(CC) $(SRC) $(MIN) $(FLAGS) $(NAME)

all: $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

