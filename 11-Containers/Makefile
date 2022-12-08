NAME	=	containers
SRCS	=	main.cpp
OBJS	=	${SRCS:.cpp=.o}
CC		=	c++
FLAGS	=	-Wall -Werror -Wextra -std=c++98

$(NAME) : $(OBJS)
	@printf "\e[92mSto compilando $@\e[39m\n"
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

%.o : %.cpp
	$(CC) $(FLAGS) $< -o $@ 

all : $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
