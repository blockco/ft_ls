#include "ft_ls.h"

void	initstruct(struct s_dir *curr, char *str, int i)
{
	DIR				*dir;
	int				temp;
	struct dirent	*dp;
	struct stat		sb_l;

	curr->blocks = 0;
	mallocstruct(&curr);
	errno = 0;
	dir = opendir(str);
	if (errno == EACCES)
		return ;
	while ((dp = readdir(dir)) != NULL)
	{
		if (-1 == lstat(makepath(str, dp->d_name), &sb_l))
		{
			perror("name overload");
			exit(EXIT_FAILURE);
		}
		curr->list[i] = ft_strdup(dp->d_name);
		temp = getlnk(sb_l, &curr, i);
		curr->blocks += temp;
		if (curr->visible[i++] == 0)
			curr->v_block += temp;
	}
	closedir(dir);
}

int		checkinf(char *str)
{
	if ((ft_strcmp(str, ".") == 0) || (ft_strcmp(str, "..") == 0))
		return (0);
	return (1);
}

char	**dup_strarray(struct s_dir **current, char **list)
{
	char	**ret;
	int		x;

	ret = ft_memalloc(sizeof(char *) * (*current)->msize);
	x = -1;
	while (++x < (*current)->msize)
		ret[x] = ft_strdup(list[x]);
	return (ret);
}

int		name_sort(struct s_dir **current, int pos1, int pos2)
{
	struct s_dir *curr;

	curr = *current;
	return (ft_strcmp(curr->list[pos1], curr->list[pos2]) > 0);
}

void	lex_sort(struct s_dir **current,
	int (*sort_func)(struct s_dir **, int, int))
{
	int				iterator;
	struct s_dir	*curr;
	int				min;
	int				pos_in_list;
	int				*found;

	curr = *current;
	iterator = -1;
	found = ft_memalloc(sizeof(int) * curr->msize);
	while (++iterator < curr->msize)
	{
		min = -1;
		pos_in_list = -1;
		while (++pos_in_list < curr->msize)
			if (!found[pos_in_list] && (min == -1
				|| sort_func(current, min, pos_in_list)))
			{
				curr->print[iterator] = pos_in_list;
				min = pos_in_list;
			}
		found[min] = 1;
	}
	free(found);
}
