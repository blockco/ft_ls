#include "ft_ls.h"

int time_sort(struct s_dir **current, int pos1, int pos2)
{
	struct s_dir	*curr;

	curr = *current;
	if (curr->time_v[pos1] - curr->time_v[pos2] == 0)
	{
		if (curr->mtim_n[pos1] - curr->mtim_n[pos2] == 0)
			return (ft_strcmp(curr->list[pos1], curr->list[pos2]) > 0);
		else
			return (curr->mtim_n[pos1] - curr->mtim_n[pos2] < 0);
	}
	else
		return (curr->time_v[pos1] - curr->time_v[pos2] < 0);
}

void	findmax(struct s_dir *curr)
{
	int	i;

	i = 0;
	curr->linksize = 0;
	while (curr->list[i])
	{
		if (curr->visible[i])
		{
			if (ft_strlen(curr->l_count[i]) > curr->linksize && curr->visible[i])
				curr->linksize = ft_strlen(curr->l_count[i]);
			if (ft_strlen(curr->list[i]) > curr->longest && curr->visible[i])
				curr->longest = ft_strlen(curr->list[i]);
			if (ft_strlen(curr->owner[i]) > curr->ownersize && curr->visible[i])
				curr->ownersize = ft_strlen(curr->owner[i]);
			if (ft_strlen(ft_itoa_base(curr->size[i], 10)) > curr->sizeprint)
				curr->sizeprint = ft_strlen(ft_itoa_base(curr->size[i], 10));
			if (ft_strlen(ft_itoa_base(curr->block_dev[i], 10)) > curr->sizeprint)
				curr->sizeprint = ft_strlen(ft_itoa_base(curr->block_dev[i], 10));
			if (ft_strlen(curr->group[i]) > curr->groupsize)
				curr->groupsize = ft_strlen(curr->group[i]);
			if (ft_strlen(ft_itoa_base(curr->block_min[i], 10)) > curr->ran)
				curr->ran = ft_strlen(ft_itoa_base(curr->block_min[i], 10));
		}
		i++;
	}
}

char	*printlnk(char *str)
{
	struct stat sb;
	char *linkname;

	if (lstat(str, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	linkname = ft_strnew(sb.st_size);
	readlink(str, linkname, sb.st_size + 1);
	return(linkname);
}

char	*makekey(struct s_dir **current)
{
	char	*key;
	struct s_dir	*curr;

	curr = *current;
	key = betterjoin("%-12s%-", (ft_itoa_base((curr->linksize + 1), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, (ft_itoa_base((curr->ownersize + 2), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, ft_itoa_base((curr->groupsize + 2), 10));
	key = betterjoin(key, "s");
	return (key);
}

void	initflag(struct s_opt *flags, int *i, int *d_size)
{
	*i = 0;
	*d_size = 0;
	flags->l_op = 0;
	flags->reg_ls = 0;
	flags->rec_op = 0;
	flags->a_op = 0;
	flags->rev_op = 0;
	flags->t_op = 0;
}
