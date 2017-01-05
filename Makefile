CC =	gcc

FLAG = -Wall -Wextra -Werror

SRCS = 	ft_ls.c \
		libftprintf.a \


OBJS =	$(SRCS:.c=.o)

all: 	$(CC)

$(CC):
		cp ./ft_printf/libftprintf.a .
		@$(CC) $(FLAG) $(SRCS)

clean:
		@/bin/rm -f $(OBJS)

fclean:	clean
		@/bin/rm -f a.out

re: fclean all

.PHONY: all clean fclean re
