NAME = pipex

CC = gcc

FLAGS = -Wall -Wextra -Werror -I./

SRC = 	main.c \
		utils/push_swap_utils1.c \
		utils/push_swap_utils4.c \
		utils/push_swap_utils5.c \
		utils/push_swap_utils6.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) pipex.h
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ)
	@echo OK!

%.o:%.c
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
