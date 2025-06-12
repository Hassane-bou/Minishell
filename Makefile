NAME = minishell

SRC = env/shelvl.c main.c env/env_copy.c 
CC = cc
# CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
LIB = lib/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLhhAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLhhAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean