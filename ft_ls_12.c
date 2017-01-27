#include "ft_ls.h"

int		uppertest(struct s_dir *curr, int i)
{
	if (curr->list[curr->print[i]] && curr->visible[curr->print[i]]
		&& curr->isdir[curr->print[i]]
		&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		return (1);
	return (0);
}

void	structstuff(struct s_dir *curr, char *str, struct s_opt *flags)
{
	curr->msize = findmsize(str);
	initstruct(curr, str, 0);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op_l(curr, flags);
	findmax(curr);
}

void	upper_rl(char *str, int first, struct s_opt *flags)
{
	struct s_dir	*curr;
	int				i;
	char			*key;

	curr = malloc(sizeof(struct s_dir));
	structstuff(curr, str, flags);
	key = makekey(&curr);
	i = 0;
	while (i < curr->msize)
	{
		if (i == 0)
			first = moreupperl(first, str, curr, flags);
		if (curr->visible[curr->print[i]])
			evenupperr(key, curr, i, str);
		i++;
	}
	i = 0;
	while (i < curr->msize && flags->rec_op)
	{
		if (uppertest(curr, i))
			upper_rl(makepath(str, curr->list[curr->print[i]]), first, flags);
		i++;
	}
}

int		arraysize(char **ret)
{
	int	i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}

int		lhelp(int i, int inc, char **dir, int d_num)
{
	i = i + inc;
	if (d_num > 1 && (i > -1 && i < arraysize(dir)))
		ft_putendl("");
	return (i);
}
