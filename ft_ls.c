#include "ft_ls.h"

void	flagfix(int argc, const char **argv, struct s_opt *flags)
{
	if (argc > 1)
		parseinput(argv, flags, argc);
}

void	endl(struct s_opt *flags, int d_size, struct s_dir *curr)
{
	if ((flags->t_op || flags->rec_op) && (d_size > 0 && curr->msize > 1))
		ft_putendl("");
}

int		main(int argc, char const *argv[])
{
	struct s_opt *flags;
	char **dirs;
	int d_size;
	struct s_dir *curr;
	char *key;
	int inc;
	int i;

	dirs = NULL;
	curr = malloc(sizeof(struct s_dir));
	flags = malloc(sizeof(struct s_opt));
	initflag(flags, &i, &d_size);
	dirs = finishmain(argc, dirs, &d_size, argv);
	flagfix(argc, argv, flags);
	if (d_size == 0)
		dirs = fixdir(dirs, &d_size);
	dirs = checkexist(dirs, d_size, curr, flags);
	key = fixmain(curr, flags);
	mainops(flags, curr, &i, &inc);
	mainprint(flags, key, i, curr);
	endl(flags, d_size, curr);
	dispatchls(flags, dirs, d_size);
	freestuff(flags, dirs, key);
}
