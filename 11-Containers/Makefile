NAME	=	containers
SRCS	=	main.cpp
OBJS	=	${SRCS:.cpp=.o}
CC		=	c++
FLAGS	=	-Wall -Werror -Wextra -std=c++98
# FLAGS	=	-Wall -Werror -Wextra -std=c++11 -g

all : $(NAME)
$(NAME) : $(OBJS)
	@printf "\e[92mSto compilando $@\e[39m\n"
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

%.o : %.cpp
	$(CC) $(FLAGS) $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) main.o mine.txt

re: fclean all

.PHONY: all clean fclean re
