NAME = pipex

CC = gcc

FLAGS = -Wall -Wextra -Werror -I./

SRC = 	src/call.c \
		src/main.c \
		src/pipex.c \
		utils/pipex_utils1.c \
		utils/pipex_utils2.c \
		utils/pipex_utils3.c \
		utils/pipex_utils4.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) pipex.h
	$(CC) -o $(NAME) $(FLAGS) $(OBJ)

%.o:%.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
