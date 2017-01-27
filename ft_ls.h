/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 03:33:34 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:54:21 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

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

# define SIXMONTHS ((365 / 2) * 86400)

typedef	struct	s_dir
{
	long		*savetime;
	int			*old;
	char		**year;
	long		msize;
	int			curdir;
	size_t		groupsize;
	size_t		ownersize;
	size_t		sizeprint;
	size_t		longest;
	size_t		linksize;
	char		**l_count;
	char		**owner;
	char		**list;
	int			*isdir;
	long		*size;
	long		*time_v;
	int			hasblock;
	char		**atim;
	long long	*atim_s;
	long		*atim_n;
	char		**mtim;
	long long	*mtim_s;
	long		*mtim_n;
	long		*t_value;
	char		**ctim;
	long long	*ctim_s;
	long		*ctim_n;
	char		**permd;
	char		**group;
	int			*visible;
	int			*isblock;
	long		*block_dev;
	long		*block_min;
	int			*print;
	long long	blocks;
	long long	v_block;
	int			*islnk;
	size_t		ran;
}				t_dir;

typedef	struct	s_opt
{
	int			l_op;
	int			reg_ls;
	int			rec_op;
	int			a_op;
	int			rev_op;
	int			t_op;
}				t_opt;

typedef struct	s_mor
{
	char		**dirs;
	int			d_size;
	char		*key;
	int			inc;
	int			i;
}				t_mor;

typedef struct	s_emor
{
	char		**ret;
	DIR			*dir;
	int			i;
	int			a;
	int			b;
	int			found;
}				t_emor;

void			exitf(char **str, int i);
void			freedub(char **data);
void			moredirfree(struct s_dir *curr);
void			freedir(struct s_dir *curr);
void			freestuff(t_opt *flags, char **dirs, char *key);
void			freestuffagain(t_opt *flags, char *key);
void			timefix(char *time_s);
void			trimtime(char *time_s);
char			*denyname(char *str);
int				findmsize(char *str);
void			mallocrest(struct s_dir **current);
void			mallocstruct(struct s_dir **current);
char			*intit_perm(int isdir, int islnk);
char			*findperm(char c);
char			*permstr(char *perm, int isdir, int isdev, int islnk);
char			*makepath(char *curdir, char *file);
char			*getyear(char *str);
void			morelink(struct stat sb_l, struct s_dir *curr, int i);
void			evenmorelnk(struct stat sb_l, struct s_dir *curr, int i);
int				getlnk(struct stat sb, struct s_dir **current, int i);
void			initial(struct s_dir **current, char **str);
void			initstruct(struct s_dir *curr, char *str, int i);
int				checkinf(char *str);
char			**dup_strarray(struct s_dir **current, char **list);
int				name_sort(struct s_dir **current, int pos1, int pos2);
void			lex_sort(struct s_dir **current,
				int (*sort_func)(struct s_dir **, int, int));
int				time_sort(struct s_dir **current, int pos1, int pos2);
void			findmax(struct s_dir *c);
char			*printlnk(char *str);
char			*makekey(struct s_dir **current);
void			initflag(t_opt *flags, int *i, int *d_size);
void			noz(char c);
void			checkflag(char c, t_opt *flags);
void			printflags(t_opt *flags);
int				moreparse(int i, int c, const char **input, t_opt *flags);
char			*parseinput(const char **input, t_opt *flags, int argc);
char			*normkey(struct s_dir *curr);
void			makevisible(struct s_dir *curr);
void			handle_op(struct s_dir *curr, t_opt *flags);
void			normprint(struct s_dir *curr);
char			*quickdirchange(char *str);
void			morenorm(struct s_dir *curr, char *str, t_opt *flags);
int				morestuff(int first, char *str,
				t_opt *flags, struct s_dir *curr);
int				checkifnorm(struct s_dir *curr, int i);
void			dosome(int first);
void			moresome(int *i, int *inc, t_opt *flags, struct s_dir *curr);
void			ls_norm(char *str, t_opt *flags, int first);
void			makerev(struct s_dir *curr);
void			handle_op_l(struct s_dir *curr, t_opt *flags);
char			*yearswitch(char *str, char *year);
char			*settime(char *str, int old, char *year);
void			revprint_l(struct s_dir *curr, char *str);
void			printrest(struct s_dir *curr, int i);
int				moreupperl(int first, char *str, struct s_dir *curr,
				t_opt *f);
void			evenupperr(char *key, struct s_dir *curr, int i, char *str);
int				uppertest(struct s_dir *curr, int i);
void			structstuff(struct s_dir *curr, char *str, t_opt *flags);
void			upper_rl(char *str, int first, t_opt *flags);
int				arraysize(char **ret);
int				lhelp(int i, int inc, char **dir, int d_num);
int				mhelp(int i, int inc, char **dir, int d_num);
void			handlerev(t_opt *flags, int *i, int *inc, int d_num);
void			dispatchls(t_opt *flags, char **dir, int d_num);
int				shelp(const char **argv, int count, char **ret, int i);
int				retit(const char **argv, int i, int *count);
void			intitthem(int *opend, int *i, int *count);
char			**storedirs(const char **argv, int *count, int argc);
int				founddir(char **dirs, int found, int i);
void			setthem(int *a, int *i, int *b, int *found);
int				seti(int i, char **dirs, DIR *dir);
void			makenull(int a, int b, char **ret, char **temp);
void			lastexist(struct s_dir *curr, int d_size, char **ret);
char			**checkexist(char **dirs, int d_size,
				struct s_dir *c, t_opt *f);
void			mainops(t_opt *flags, struct s_dir *curr, int *i, int *inc);
int				checkinc(t_opt *flags, struct s_dir *curr);
void			mainprint(t_opt *flags, char *key, int i, struct s_dir *curr);
char			*fixmain(struct s_dir *curr, t_opt *flags);
char			**fixdir(char **dirs, int *d_size);
char			**finishmain(int argc, char **dirs, int *d_size,
				const char **argv);
void			flagfix(int argc, const char **argv, t_opt *flags);
void			endl(t_opt *flags, int d_size, struct s_dir *curr);
void			revprint(struct s_dir *curr);
#endif
