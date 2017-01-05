#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <stdlib.h>
# include "./ft_printf/ft_printf.h"

typedef	struct	h_dir
{
	//
	int msize;
	int curdir;
	//
	char **list;
	int *isdir;
	long *size;
	char **atim;
	char **mtim;
	char **ctim;
	char **permd;
	char **group;
	//imp
	int *visible;
	int *print;
	size_t longest;
}				h_dir;

void lex_sort(h_dir **curr, int (*sort_func)(h_dir **, int, int));
#endif
