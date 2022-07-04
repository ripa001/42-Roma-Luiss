NAME = harl
CC = c++
SRCS = $(addprefix src/, main.cpp Harl.cpp)
CFLAGS= -Wall -Wextra -Werror -std=c++98

all: $(NAME)
$(NAME): $(SRCS)
	@printf "\e[92mSto compilando $@\e[39m\n"
	@$(CC) $(CFLAGS) -o $@ $^

test: re
	@./$(NAME)
clean:
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re