NAME = replace
CC = c++
SRCS = main.cpp
CFLAGS= -Wall -Wextra -Werror -std=c++98

all: $(NAME)
$(NAME): $(SRCS)
	@printf "\e[92mSto compilando $@\e[39m\n"
	@$(CC) $(CFLAGS) -o $@ $^

test: re
	@./$(NAME) test/empty.txt a b
	@./$(NAME) test/lorem.txt ", " "	"
	@./$(NAME) test/test.txt Fizz waaa
clean:
fclean: clean
	rm -rf $(NAME) test/empty.replace test/test.replace test/lorem.replace
re: fclean all
.PHONY: all clean fclean re