CC =	gcc

FLAG = -Wall -Wextra -Werror

SRCS = 	ft_ls.c \
		libftprintf.a \


OBJS =	$(SRCS:.c=.o)

all: 	$(CC)

$(CC):
		cp ./ft_printf/libftprintf.a .
		@$(CC) $(FLAG) $(SRCS) -o ft_ls

clean:
		@/bin/rm -f $(OBJS)

fclean:	clean
		@/bin/rm -f ft_ls

re: fclean all

.PHONY: all clean fclean re
