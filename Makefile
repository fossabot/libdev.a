# Makefile
NAME =		libdev
CC =		gcc
LIB =		ar
CFLAGS =	-Wall -Wextra -Werror -I.
LFLAGS =	-cq
SRCS =		$(wildcard *.c)
OBJS =		$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LIB) $(LFLAGS) $(NAME).a $(OBJS)

test: $(NAME)
	cd tests && make

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME).a

re: fclean all

.PHONY: re fclean all
