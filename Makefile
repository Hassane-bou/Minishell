CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c
LIBS = -lreadline

OBJE = $(SRCS:.c=.o)

NAME = parse

all: $(NAME)

$(NAME):$(OBJE)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJE)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

