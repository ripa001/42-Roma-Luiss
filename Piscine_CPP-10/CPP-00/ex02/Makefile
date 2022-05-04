NAME = account
CC = c++
SRCS = Account.cpp test.cpp
CFLAGS= -Wall -Wextra -Werror -std=c++98

all: $(NAME)
$(NAME): $(SRCS)
	@echo "Sto compilando $@"
	@$(CC) $(CFLAGS) -o $@ $^
clean:
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re