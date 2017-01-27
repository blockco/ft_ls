#include "ft_ls.h"

int		mhelp(int i, int inc, char **dir, int d_num)
{
	i = i + inc;
	if (d_num > 1 && (i > -1 && i < arraysize(dir)))
		ft_putendl("");
	return (i);
}

void	handlerev(struct s_opt *flags, int *i, int *inc, int d_num)
{
	if (flags->rev_op)
	{
		*i = d_num - 1;
		*inc = -1;
	}
	else
	{
		*i = 0;
		*inc = 1;
	}
}

void	dispatchls(struct s_opt *flags, char **dir, int d_num)
{
	int i;
	int inc;

	handlerev(flags, &i, &inc, d_num);
	if (!flags->l_op)
	{
		while (i > -1 && i < arraysize(dir))
		{
			if (d_num > 1 && dir[i])
				ft_putendl(betterjoin(dir[i], ":"));
			ls_norm(dir[i], flags, 0);
			i = lhelp(i, inc, dir, d_num);
		}
	}
	else
	{
		while (i > -1 && i < d_num && dir[i])
		{
			if (d_num > 1 && dir[i])
				ft_putendl(betterjoin(dir[i], ":"));
			upper_rl(dir[i], 0, flags);
			i = mhelp(i, inc, dir, d_num);
		}
	}
}

int		shelp(const char **argv, int count, char **ret, int i)
{
	ret[count] = ft_strdup(argv[i]);
	count = count + 1;
	return (count);
}

int		retit(const char **argv, int i, int *count)
{
	if (argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1]))
		*count = *count + 1;
	i++;
	return (i);
}
