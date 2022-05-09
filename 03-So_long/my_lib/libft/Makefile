NAME = libft.a
SRCS = ft_bzero.c\
	ft_isalnum.c\
	ft_atoi.c\
	ft_itoa.c\
	ft_isdigit.c\
	ft_isalpha.c\
	ft_isprint.c\
	ft_isascii.c\
	ft_memset.c\
	ft_memcmp.c\
	ft_memchr.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_strncmp.c\
	ft_strlen.c\
	ft_strchr.c\
	ft_bzero.c\
	ft_strdup.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_calloc.c\
	ft_strnstr.c\
	ft_split.c\
	ft_strjoin.c\
	ft_substr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c
	  
FLAGS = -Wall -Werror -Wextra -c
CC = gcc
OBJS = $(SRCS:.c=.o)
BONUS = ft_lstadd_front.c\
		ft_lstnew.c\
		ft_lstsize.c\
		ft_lstadd_back.c\
		ft_lstlast.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c
OBJS_BONUS = $(BONUS:.c=.o)
$(NAME):
	$(CC) $(FLAGS) $(SRCS)
	ar rcs libft.a $(OBJS)
all: $(NAME)
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:		clean
	rm -f $(NAME)
re: fclean all
bonus:
	$(CC) $(FLAGS) $(BONUS)
	ar rcs libft.a $(OBJS_BONUS)