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

void	freedub(char **data);
void	moredirfree(h_dir *curr);
void	freedir(h_dir *curr);
void 	freestuff(t_opt *flags, char **dirs, char *key);
void	freestuffagain(t_opt *flags, char *key);
void	timefix(char *time_s);
void	trimtime(char *time_s);
char	*denyname(char *str);
int		findmsize(char *str);
void	mallocrest(h_dir **current);
void	mallocstruct(h_dir **current);
char	*intit_perm(int isdir, int islnk);
char	*findperm(char c);
char* 	permstr(char *perm, int isdir, int isdev, int islnk);
char*	makepath(char *curdir, char *file);
char*	getyear(char *str);
void	morelink(struct stat sb_l, h_dir *curr, int i);
void	evenmorelnk(struct stat sb_l, h_dir *curr, int i);
int		getlnk(struct stat sb_l, h_dir **current, int i);
void 	initial(h_dir **current, char **str);
void	initstruct(h_dir *curr, char *str, int i);
int		checkinf(char *str);
char	**dup_strarray(h_dir **current, char **list);
int		name_sort(h_dir **current, int pos1, int pos2);
void	lex_sort(h_dir **current, int (*sort_func)(h_dir **, int, int));
int		time_sort(h_dir **current, int pos1, int pos2);
void	findmax(h_dir *curr);
char	*printlnk(char *str);
char*	makekey(h_dir **current);
void	initflag(t_opt *flags, int *i, int *d_size);
void	noz(char c);
void	checkflag(char c, t_opt *flags);
void	printflags(t_opt *flags);
int		moreparse(int i, int c, const char **input, t_opt *flags);
char	*parseinput(const char **input, t_opt *flags, int argc);
char*	normkey(h_dir *curr);
void	makevisible(h_dir *curr);
void	handle_op(h_dir *curr, t_opt *flags);
void	normprint(h_dir *curr);
char	*quickdirchange(char *str);
void	morenorm(h_dir *curr, char *str, t_opt *flags);
int		morestuff(int first, char *str, t_opt *flags, h_dir *curr);
int		checkifnorm(h_dir *curr, int i);
void	dosome(int first);
void	moresome(int *i, int *inc, t_opt *flags, h_dir *curr);
void	ls_norm(char *str, t_opt *flags, int first);
void	makerev(h_dir *curr);
void	handle_op_l(h_dir *curr, t_opt *flags);
char	*yearswitch(char *str, char *year);
char*	settime(char *str, int old, char *year);
void	revprint_l(h_dir *curr, char *str);
void	printrest(h_dir *curr, int i);
int		moreupperl(int first, char *str, h_dir *curr, t_opt *flags);
void 	evenupperr(char *key, h_dir *curr, int i, char *str);
int		uppertest(h_dir *curr, int i);
void	structstuff(h_dir *curr, char *str, t_opt *flags);
void	upper_rl(char *str, int first, t_opt *flags);
int		arraysize(char** ret);
int		lhelp(int i, int inc, char **dir, int d_num);
int		mhelp(int i, int inc, char **dir, int d_num);
void	handlerev(t_opt *flags, int *i, int *inc, int d_num);
void	dispatchls(t_opt *flags, char **dir, int d_num);
int		shelp(const char **argv, int count, char **ret, int i);
int		retit(const char **argv, int i, int *count);
void	intitthem(int *opend, int *i, int *count);
char	**storedirs(const char **argv, int *count, int argc);
int		founddir(char **dirs, int found, int i);
void	setthem(int *a, int *i, int *b, int *found);
int		seti(int i, char **dirs, DIR *dir);
void	makenull(int a, int b, char **ret, char **temp);
void	lastexist(h_dir *curr, int d_size, char **ret);
char	**checkexist(char **dirs, int d_size, h_dir *curr, t_opt *flags);
void	mainops(t_opt *flags, h_dir *curr, int *i, int *inc);
int		checkinc(t_opt *flags, h_dir *curr);
void	mainprint(t_opt *flags, char *key, int i, h_dir *curr);
char	*fixmain(h_dir *curr, t_opt *flags);
char	**fixdir(char **dirs, int *d_size);
char	**finishmain(int argc, char **dirs, int *d_size, const char **argv);
void	flagfix(int argc, const char **argv, t_opt *flags);
void	endl(t_opt *flags, int d_size, h_dir *curr);

#endif
