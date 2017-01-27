CC =	gcc

FLAG = -Wall -Wextra -Werror

SRCS = 	ft_ls.c \
		ft_ls_1.c \
		ft_ls_2.c \
		ft_ls_3.c \
		ft_ls_4.c \
		ft_ls_5.c \
		ft_ls_6.c \
		ft_ls_7.c \
		ft_ls_8.c \
		ft_ls_9.c \
		ft_ls_10.c \
		ft_ls_11.c \
		ft_ls_12.c \
		ft_ls_13.c \
		ft_ls_14.c \
		ft_ls_15.c \
		ft_ls_16.c \
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
