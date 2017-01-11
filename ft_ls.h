#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include "./ft_printf/ft_printf.h"

typedef	struct	h_dir
{
	//
	int msize;
	int curdir;
	size_t groupsize;
	size_t ownersize;
	size_t sizeprint;
	size_t longest;
	//
	char **owner;
	char **list;
	int *isdir;
	long *size;

	char **atim;
	long long *atim_s;
	long *atim_n;

	char **mtim;
	long long *mtim_s;
	long *mtim_n;

	char **ctim;
	long long *ctim_s;
	long *ctim_n;

	char **permd;
	char **group;
	//imp
	int *visible;
	int *print;
	int time_v;
	long long blocks;
	int *islnk;
}				h_dir;

void lex_sort(h_dir **curr, int (*sort_func)(h_dir **, int, int));
#endif
