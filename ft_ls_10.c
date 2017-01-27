#include "ft_ls.h"

void	moresome(int *i, int *inc, struct s_opt *flags, struct s_dir *curr)
{
	if (flags->rev_op)
		*i = curr->msize - 1;
	else
		*inc = 1;
}

void	ls_norm(char *str, struct s_opt *flags, int first)
{
	struct s_dir	*curr;
	int				i;
	char			*temp;
	int				inc;

	inc = -1;
	i = 0;
	curr = malloc(sizeof(struct s_dir));
	curr->msize = findmsize(str);
	if (curr->msize == 0)
		return ;
	morenorm(curr, str, flags);
	temp = makepath(str, curr->list[curr->print[0]]);
	temp[ft_strlen(temp) - 2] = '\0';
	first = morestuff(first, str, flags, curr);
	moresome(&i, &inc, flags, curr);
	while (i > -1 && i < curr->msize && flags->rec_op)
	{
		if (checkifnorm(curr, i))
		{
			dosome(first);
			ls_norm(makepath(str, curr->list[curr->print[i]]), flags, first);
		}
		i = i + inc;
	}
}

void	makerev(struct s_dir *curr)
{
	int	i;
	int	*ret;
	int count;

	count = 0;
	i = curr->msize;
	ret = (int*)malloc(sizeof(int) * curr->msize);
	i--;
	while (i > -1)
	{
		ret[count] = curr->print[i];
		i--;
		count++;
	}
	curr->print = ret;
}

void	handle_op_l(struct s_dir *curr, struct s_opt *flags)
{
	if (flags->a_op)
		makevisible(curr);
	if (flags->rev_op)
		makerev(curr);
}

char	*yearswitch(char *str, char *year)
{
	int		i;
	char	*ret;
	char	*c;

	c = ft_strchr(year, '\n');
	c[0] = 0;
	ret = ft_strnew(7);
	i = 0;
	while (i < 7)
	{
		ret[i] = str[i];
		i++;
	}
	ret = betterjoin(ret, " ");
	return (betterjoin(ret, year));
}
