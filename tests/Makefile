NAME =		libdev.a-test
CC =		gcc
CFLAGS = 	-Wall -Wextra -Werror -I.. -L.. -ldev -g
SRCS =		main.c
OBJS = 		$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean
