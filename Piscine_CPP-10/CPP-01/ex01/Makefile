NAME = zombie
CC = c++
SRCS = $(addprefix src/, newZombie.cpp randomChump.cpp main.cpp Zombie.cpp zombieHorde.cpp)
CFLAGS= -Wall -Wextra -Werror -std=c++98

all: $(NAME)
$(NAME): $(SRCS)
	@printf "\e[92mSto compilando $@\e[39m\n"
	@$(CC) $(CFLAGS) -o $@ $^
clean:
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re