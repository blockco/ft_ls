#include "ft_ls.h"

char	*settime(char *str, int old, char *year)
{
	int i;
	int a;
	char *ret;
	ret = ft_strnew(15);
	i = 4;
	a = 0;
	while (i < 16)
	{
		ret[a] = str[i];
		a++;
		i++;
	}
	if (old)
		return(yearswitch(ret, year));
	return (ret);
}

void	revprint_l(struct s_dir *curr, char *str)
{
	int	temp;

	temp = curr->msize;
	temp--;
	while (temp > -1)
	{
		if (curr->visible[curr->print[temp]])
		{
			ft_printf(makekey(&curr), curr->permd[curr->print[temp]], curr->l_count[curr->print[temp]] ,curr->owner[curr->print[temp]], curr->group[curr->print[temp]],
			ft_itoa_base(curr->size[curr->print[temp]], 10), settime(curr->mtim[curr->print[temp]],curr->old[curr->print[temp]], curr->year[curr->print[temp]]), curr->list[curr->print[temp]]);
			if (curr->islnk[curr->print[temp]])
				ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[temp]])));
			if (curr->visible[curr->print[temp]])
				ft_putchar('\n');
		}
		temp--;
	}
}

void	printrest(struct s_dir *curr, int i)
{
	char	*key;

	key = ft_strdup("%s%s%s%s%s%s%-13s%-0s");
	if (curr->isblock[i])
	{
		ft_printf(key, makespace(curr->sizeprint - ft_strlen(ft_itoa_base(curr->block_dev[i] + 1, 10)), ' '),
		ft_itoa_base(curr->block_dev[i], 10), ",", makespace((curr->ran - ft_strlen(ft_itoa_base(curr->block_min[i], 10)) + 1), ' '), ft_itoa_base(curr->block_min[i], 10),  " ",settime(curr->mtim[i],curr->old[i], curr->year[i]), curr->list[i],
		curr->list[i]);
		return;
	}
	if (curr->hasblock)
	{
		ft_printf("%s", makespace((curr->ran + 2), ' '));
	}
	key = ft_strdup("%s%s%s%-13s%-0s");
	ft_printf(key, makespace(curr->sizeprint - ft_strlen(ft_itoa_base(curr->size[i], 10)), ' '),
	ft_itoa_base(curr->size[i], 10), " ", settime(curr->mtim[i],curr->old[i], curr->year[i]), curr->list[i]);
}

int		moreupperl(int first, char *str, struct s_dir *curr, struct s_opt *flags)
{
	if (first++)
		ft_printf("\n%s:\n", quickdirchange(str));
	if (flags->a_op)
		curr->v_block = 0;
	if (curr->blocks - curr->v_block > -1)
		ft_printf("%s%lld\n", "total ",(curr->blocks - curr->v_block));
	return (first);
}

void	evenupperr(char *key, struct s_dir *curr, int i, char *str)
{
	ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]]);
	printrest(curr, curr->print[i]);
	if (curr->islnk[curr->print[i]])
		ft_printf("%s%s\n", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
	else
		ft_putchar('\n');
}
