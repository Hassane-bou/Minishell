CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SRCS = main.c utils.c ft_split.c ft_substr.c parse.c tokens.c ft_strdup.c\
		check_syntaxe.c expand.c

LIBS = -lreadline

OBJE = $(SRCS:.c=.o)

NAME = parse

all: $(NAME)

$(NAME):$(OBJE)
		$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME) 

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJE)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

