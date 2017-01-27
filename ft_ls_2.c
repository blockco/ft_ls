#include "ft_ls.h"

void	timefix(char *time_s)
{
	time_s = ft_strsub(time_s, 5, (ft_strlen(time_s) - 5));
}

void	trimtime(char *time_s)
{
	time_s[ft_strlen(time_s) - 1] = 0;
	timefix(time_s);
}

char	*denyname(char *str)
{
	int		i;
	int		a;
	char	*ret;

	i = 2;
	a = 0;
	ret = malloc(ft_strlen(str) - 1);
	while (str[i])
	{
		ret[a] = str[i];
		i++;
		a++;
	}
	ret[a] = '\0';
	return (ret);
}

int		findmsize(char *str)
{
	int				msize;
	DIR				*dir;
	struct dirent	*dp;

	msize = 0;
	errno = 0;
	dir = opendir(str);
	if (errno == EACCES)
	{
		ft_printf("%s:\n%s%s%s\n", str, "ls: ", denyname(str),
		": Permission denied");
		return (0);
	}
	if (dir)
	{
		while ((dp = readdir(dir)) != NULL)
			msize++;
		closedir(dir);
	}
	return (msize);
}

void	mallocrest(struct s_dir **current)
{
	struct s_dir	*curr;

	curr = *current;
	curr->ctim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->ctim_s = (long long*)malloc(sizeof(long long) * curr->msize);
	curr->ctim_n = (long*)malloc(sizeof(long) * curr->msize);
	curr->time_v = (long*)malloc(sizeof(long) * curr->msize);
	curr->permd = (char**)malloc(sizeof(char*) * curr->msize);
	curr->group = (char**)malloc(sizeof(char*) * curr->msize);
	curr->visible = (int*)malloc(sizeof(int) * curr->msize);
	curr->print = (int*)malloc(sizeof(int) * curr->msize);
	curr->owner = (char**)malloc(sizeof(char*) * curr->msize);
	curr->islnk = (int*)malloc(sizeof(int) * curr->msize);
	curr->isblock = (int*)malloc(sizeof(int) * curr->msize);
	curr->block_dev = (long*)malloc(sizeof(long) * curr->msize);
	curr->block_min = (long*)malloc(sizeof(long) * curr->msize);
}
