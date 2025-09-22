CC = cc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
# CFLAGS = 
SRCS = main.c utils.c ft_split.c ft_substr.c parse.c tokens.c ft_strdup.c\
		check_syntaxe.c expand.c utils_syntaxe.c utils_tokens.c\
		utils_parse.c utils_libft.c expand_string.c expand_utils.c

LIBS = -lreadline

OBJE = $(SRCS:.c=.o)

NAME = parse

all: $(NAME)

# $(NAME):$(OBJE)
# 		$(CC) $(CFLAGS) $(OBJE) $(LIBS) -o $(NAME) 


$(NAME): $(OBJE)
	$(CC) $(OBJE) $(CFLAGS) $(LIBS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJE)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

