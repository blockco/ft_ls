#include "ft_ls.h"

int		seti(int i, char **dirs, DIR *dir)
{
	if (errno != 2 && !dirs[i])
		closedir(dir);
	i++;
	return (i);
}

void	makenull(int a, int b, char **ret, char **temp)
{
	ret[a] = NULL;
	temp[b] = NULL;
}

void	lastexist(struct s_dir *curr, int d_size, char **ret)
{
	curr->list = (char**)malloc(sizeof(char*) * d_size + 1);
	ret[d_size] = NULL;
}
char	**checkexist(char **dirs, int d_size, struct s_dir *curr, struct s_opt *flags)
{
	char	**ret;
	DIR		*dir;
	int		i;
	int		a;
	int		b;
	int		found;

	setthem(&a, &i, &b, &found);
	ret = (char**)malloc(sizeof(char*) * d_size + 1);
	lastexist(curr, d_size, ret);
	while (i < d_size)
	{
		if (NULL == (dir = opendir (dirs[i])))
		{
			if (errno == 20 || (errno == 2 && !flags->rec_op))
				curr->list[b++] = ft_strdup(dirs[i]);
			else if (errno > 0)
				found = founddir(dirs, found, i);
		}
		else
			ret[a++] = ft_strdup(dirs[i]);
		i = seti(i, dirs, dir);
	}
	makenull(a, b, ret, curr->list);
	return(ret);
}

void	mainops(struct s_opt *flags, struct s_dir *curr, int *i, int *inc)
{
	if (flags->rev_op && (!flags->rec_op && curr->msize > 0))
	{
		*i = curr->msize - 1;
		*inc = -1;
	}
	else
	{
		*i = 0;
		*inc = 1;
	}
}
