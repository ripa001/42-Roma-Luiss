NAME = miniRT
CC = gcc
SRC = main.c utility.c utility2.c utility3.c ft_split.c check.c mlx_utility.c \
		vec_op.c vec_op2.c lighting.c ray.c matrix.c camera.c vector_rotation.c \
		rotation.c add_obj.c transform.c intersections.c intersections2.c primitives.c\
		hooks.c vec_util.c bump_and_texture.c update_obj.c
# MLX_FLAG = -l mlx -framework openGL -framework AppKit -g
MLX_FLAG = -l mlx -framework openGL -framework AppKit -g
GNL_SRC = get_next_line.c get_next_line_utils.c
GNL_DIR = get_next_line
GNL = $(addprefix $(GNL_DIR)/, $(GNL_SRC))
OBJ = $(SRC) $(GNL)

%.o: %.c $(OBJ)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAG) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all
