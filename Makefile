CC =	gcc

FLAG = -Wall -Wextra -Werror

SRCS = 	ft_ls.c \
		libftprintf.a \


OBJS =	$(SRCS:.c=.o)

COMP =	make -C $(FT_PRINTF) re

FT_PRINTF = ft_printf/

all: 	$(CC)

$(CC):
		@$(COMP)
		cp ./ft_printf/libftprintf.a .
		@$(CC) $(FLAG) $(SRCS) -o ft_ls

clean:
		@/bin/rm -f $(OBJS) ft_ls

fclean:	clean
		@/bin/rm -f ft_ls

re: fclean all

.PHONY: all clean fclean re
