NAME = pipex
SRCS = pipex.c ft_split.c ft_strlen.c ft_strdup.c ft_substr.c ft_strjoin.c pipex_utils.c ft_strcmp.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
