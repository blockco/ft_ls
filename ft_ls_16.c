#include "ft_ls.h"

int		checkinc(struct s_opt *flags, struct s_dir *curr)
{
	if (flags->rev_op && (!flags->rec_op && curr->msize > 0))
		return (-1);
	else
		return (1);
}

void	mainprint(struct s_opt *flags, char *key, int i, struct s_dir *curr)
{
	int	inc;

	inc = checkinc(flags, curr);
	while (i < curr->msize)
	{
		if (flags->l_op)
		{
			ft_printf(key, curr->permd[curr->print[i]],
				curr->l_count[curr->print[i]],
				curr->owner[curr->print[i]], curr->group[curr->print[i]]);
			printrest(curr, curr->print[i]);
			if (curr->islnk[curr->print[i]])
				ft_printf("%s%s\n", " -> ",
				printlnk(makepath(".", curr->list[curr->print[i]])));
			else
				ft_putchar('\n');
		}
		else if (flags->t_op)
			ft_putendl(curr->list[curr->print[i]]);
		else
			ft_putendl(curr->list[curr->print[i]]);
		i = i + inc;
		if (!curr->list[i])
			break ;
	}
}

char	*fixmain(struct s_dir *curr, struct s_opt *flags)
{
	char **temp;

	temp = curr->list;
	curr->msize = arraysize(temp);
	initial(&curr, temp);
	findmax(curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	return (makekey(&curr));
}

char	**fixdir(char **dirs, int *d_size)
{
	dirs = (char**)malloc(sizeof(char*) * 2);
	dirs[0] = ft_strdup(".");
	dirs[1] = NULL;
	*d_size = 1;
	return (dirs);
}

char	**finishmain(int argc, char **dirs, int *d_size, const char **argv)
{
	if (argc > 1)
	{
		dirs = storedirs(argv, d_size, argc);
		return (dirs);
	}
	return (NULL);
}
