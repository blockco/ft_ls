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

#define	SIXMONTHS	((365 / 2) * 86400)

typedef	struct	h_dir
{
	long *savetime;
	int *old;
	char **year;
	//
	long msize;
	int curdir;
	size_t groupsize;
	size_t ownersize;
	size_t sizeprint;
	size_t longest;
	size_t linksize;
	//
	char **l_count;

	char **owner;
	char **list;
	int *isdir;
	long *size;
	long *time_v;
	int hasblock;

	char **atim;
	long long *atim_s;
	long *atim_n;



	char **mtim;
	long long *mtim_s;
	long *mtim_n;

	long *t_value;

	char **ctim;
	long long *ctim_s;
	long *ctim_n;

	char **permd;
	char **group;
	//imp1
	int *visible;

	int *isblock;
	long *block_dev;
	long *block_min;
	int *print;
	long long blocks;
	long long v_block;
	int *islnk;
	size_t ran;
}				h_dir;

typedef	struct	t_opt
{
	int l_op;
	int reg_ls;
	int rec_op;
	int a_op;
	int rev_op;
	int t_op;
}				t_opt;
//sorting
	//base call
void lex_sort(h_dir **curr, int (*sort_func)(h_dir **, int, int));
	//name
int	name_sort(h_dir **current, int pos1, int pos2);
	//time
int time_sort(h_dir **current, int pos1, int pos2);

//find size to malloc struct
int findmsize(char *str);

//malloc struct
void mallocstruct(h_dir **current);

//sets d in permissions
char* intit_perm(int isdir, int islnk);

//sets up the permissions
char* permstr(char *perm, int isdir, int isdev, int islnk);

//gets the info for individual peice
int getlnk(struct stat sb_l, h_dir **current, int i);

//intits struct overall
void initstruct(h_dir **current, char *str);

//makes sure it isnt root or current directory
int checkinf(char *str);

//copies strarray over
char	**dup_strarray(h_dir **current, char **list);

//find max for printing
void findmax(h_dir **current);

//fixes time for formating (NOT WORKING)
void timefix(char *time_s);

//trims endline off time
void trimtime(char *time_s);

//if link is there prints link
char *printlnk(char *str);

//Recursive LS call
void upper_rl(char *str, int first, t_opt *flags);

//makes path to make Recursive call or print directory
char* makepath(char *curdir, char *file);

#endif
