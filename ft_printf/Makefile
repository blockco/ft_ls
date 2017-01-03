CC =	gcc

FLAG =	-c -Wall -Wextra -Werror -O2

NAME =	libftprintf.a

LIB =	ar rc

RLIB =	ranlib

SRCS =	ft_printf.c \
		pf_extra.c \
		pf_functions.c \
		flags.c \
		flagfunctions.c \
		flagformating.c \
		flagformatingstrings.c \
		percdealer.c \
		signflag.c \
		zerohash.c \
		flagstrsplit.c \
		flagfunextra.c \
		flagextra.c \
		pf_extramore.c \
		pf_funmore.c \
		extraprintf.c \
		last.c \


SRCSL =	libft/ft_putchar.c \
		libft/ft_putstr.c \
		libft/ft_isalpha.c \
		libft/ft_isdigit.c \
		libft/ft_isalnum.c \
		libft/ft_isascii.c \
		libft/ft_isprint.c \
		libft/ft_toupper.c \
		libft/ft_tolower.c \
		libft/ft_atoi.c \
		libft/ft_itoa.c \
		libft/ft_strnew.c \
		libft/ft_strdel.c \
		libft/ft_strclr.c \
		libft/ft_strdup.c \
		libft/ft_strlen.c \
		libft/ft_strcpy.c \
		libft/ft_strncpy.c \
		libft/ft_strcat.c \
		libft/ft_strncat.c \
		libft/ft_strlcat.c \
		libft/ft_strchr.c \
		libft/ft_strrchr.c \
		libft/ft_strstr.c \
		libft/ft_strnstr.c \
		libft/ft_strcmp.c \
		libft/ft_strncmp.c \
		libft/ft_memset.c \
		libft/ft_bzero.c \
		libft/ft_memcpy.c \
		libft/ft_memccpy.c \
		libft/ft_memmove.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_memalloc.c \
		libft/ft_memdel.c \
		libft/ft_striter.c \
		libft/ft_striteri.c \
		libft/ft_strmap.c \
		libft/ft_strmapi.c \
		libft/ft_strequ.c \
		libft/ft_strnequ.c \
		libft/ft_strsub.c \
		libft/ft_strjoin.c \
		libft/ft_strtrim.c \
		libft/ft_strsplit.c \
		libft/ft_putendl.c \
		libft/ft_putnbr.c \
		libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_putendl_fd.c \
		libft/ft_putnbr_fd.c \

RMOBJ = ft_putchar.o \
		ft_putstr.o \
		ft_isalpha.o \
		ft_isdigit.o \
		ft_isalnum.o \
		ft_isascii.o \
		ft_isprint.o \
		ft_toupper.o \
		ft_tolower.o \
		ft_atoi.o \
		ft_itoa.o \
		ft_strnew.o \
		ft_strdel.o \
		ft_strclr.o \
		ft_strdup.o \
		ft_strlen.o \
		ft_strcpy.o \
		ft_strncpy.o \
		ft_strcat.o \
		ft_strncat.o \
		ft_strlcat.o \
		ft_strchr.o \
		ft_strrchr.o \
		ft_strstr.o \
		ft_strnstr.o \
		ft_strcmp.o \
		ft_strncmp.o \
		ft_memset.o \
		ft_bzero.o \
		ft_memcpy.o \
		ft_memccpy.o \
		ft_memmove.o \
		ft_memchr.o \
		ft_memcmp.o \
		ft_memalloc.o \
		ft_memdel.o \
		ft_striter.o \
		ft_striteri.o \
		ft_strmap.o \
		ft_strmapi.o \
		ft_strequ.o \
		ft_strnequ.o \
		ft_strsub.o \
		ft_strjoin.o \
		ft_strtrim.o \
		ft_strsplit.o \
		ft_putendl.o \
		ft_putnbr.o \
		ft_putchar_fd.o \
		ft_putstr_fd.o \
		ft_putendl_fd.o \
		ft_putnbr_fd.o \

OBJL1 =			libft/ft_putchar.o \
				libft/ft_putstr.o \
				libft/ft_isalpha.o \
				libft/ft_isdigit.o \
				libft/ft_isalnum.o \
				libft/ft_isascii.o \
				libft/ft_isprint.o \
				libft/ft_toupper.o \
				libft/ft_tolower.o \
				libft/ft_atoi.o \
				libft/ft_itoa.o \
				libft/ft_strnew.o \
				libft/ft_strdel.o \
				libft/ft_strclr.o \
				libft/ft_strdup.o \
				libft/ft_strlen.o \
				libft/ft_strcpy.o \
				libft/ft_strncpy.o \
				libft/ft_strcat.o \
				libft/ft_strncat.o \
				libft/ft_strlcat.o \
				libft/ft_strchr.o \
				libft/ft_strrchr.o \
				libft/ft_strstr.o \
				libft/ft_strnstr.o \
				libft/ft_strcmp.o \
				libft/ft_strncmp.o \
				libft/ft_memset.o \
				libft/ft_bzero.o \
				libft/ft_memcpy.o \
				libft/ft_memccpy.o \
				libft/ft_memmove.o \
				libft/ft_memchr.o \
				libft/ft_memcmp.o \
				libft/ft_memalloc.o \
				libft/ft_memdel.o \
				libft/ft_striter.o \
				libft/ft_striteri.o \
				libft/ft_strmap.o \
				libft/ft_strmapi.o \
				libft/ft_strequ.o \
				libft/ft_strnequ.o \
				libft/ft_strsub.o \
				libft/ft_strjoin.o \
				libft/ft_strtrim.o \
				libft/ft_strsplit.o \
				libft/ft_putendl.o \
				libft/ft_putnbr.o \
				libft/ft_putchar_fd.o \
				libft/ft_putstr_fd.o \
				libft/ft_putendl_fd.o \
				libft/ft_putnbr_fd.o \

OBJS =	$(SRCS:.c=.o)
OBJSL = $(SRCSL:.c=.o)

all: 	$(NAME)

$(NAME):
		@$(CC) $(FLAG) $(SRCS) $(SRCSL)
		@$(LIB) $(NAME) $(OBJS) $(RMOBJ)
		@$(RLIB) $(NAME)

clean:
		@/bin/rm -f $(OBJS) $(OBJL) $(RMOBJ) $(OBJL1)

fclean:	clean
		@/bin/rm -f $(NAME)

remove:
		@/bin/rm -f $(OBJS) $(OBJL) $(RMOBJ) $(OBJL1)

comp:
		gcc $(NAME) main.c
compde:
		gcc $(NAME) -g main.c

re: fclean all

rec:  re comp remove

.PHONY: all clean fclean re remove comp
