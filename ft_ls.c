#include "ft_ls.h"
#include <stdio.h>

int findmsize(char *str)
{
	int msize;
	DIR *dir;
	struct dirent *dp;

	msize = 0;
	dir = opendir (str);
	while ((dp = readdir (dir)) != NULL)
		msize++;
	closedir(dir);
	return msize;
}

void mallocstruct(h_dir **current)
{
	h_dir *curr;

	curr = *current;
	curr->list = (char**)malloc(sizeof(char*) * curr->msize + 1);
	curr->list[curr->msize] = NULL;
	curr->isdir = (int*)malloc(sizeof(int) * curr->msize);
	curr->size = (long*)malloc(sizeof(long) * curr->msize);
	curr->atim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->mtim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->ctim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->permd = (char**)malloc(sizeof(char*) * curr->msize);
	curr->group = (char**)malloc(sizeof(char*) * curr->msize);
	curr->visible = (int*)malloc(sizeof(int) * curr->msize);
	curr->print = (int*)malloc(sizeof(int) * curr->msize);
	curr->longest = 0;
}

char* intit_perm(int isdir)
{
	if (isdir)
		return(ft_strdup("d"));
	return(ft_strdup("-"));
}

char* permstr(char *perm, int isdir)
{
	int i;
	char *ret;
	if (isdir)
		i = 2;
	else
		i = 3;
	ret = intit_perm(isdir);
	while (perm[i])
	{
		if(perm[i] == '7')
			ret = betterjoin(ret, "rwx");
		else if (perm[i] == '6')
			ret = betterjoin(ret, "rw-");
		else if (perm[i] == '5')
			ret = betterjoin(ret, "r-x");
		else if (perm[i] == '4')
			ret = betterjoin(ret, "r--");
		else if (perm[i] == '3')
			ret = betterjoin(ret, "-wx");
		else if (perm[i] == '2')
			ret = betterjoin(ret, "-w-");
		else if (perm[i] == '1')
			ret = betterjoin(ret, "--x");
		else
			ret = betterjoin(ret, "---");
		i++;
	}
	return (ret);
}

char* makepath(char *curdir, char *file)
{
	char *temp;

	temp = betterjoin(curdir, "/");
	return(betterjoin(temp, file));
}

void initstruct(h_dir **current, char *str)
{
	DIR *dir;
	int i;
	struct dirent *dp;
	struct stat sb;
	h_dir *curr;
	int key;

	i = 0;
	curr = *current;
	mallocstruct(&curr);
	dir = opendir(str);
	while ((dp = readdir (dir)) != NULL)
	{
	   if (-1 == stat(makepath(str, dp->d_name), &sb))
	   {
		   perror("name overload");
		   exit(EXIT_FAILURE);
	   }
	   key = (sb.st_mode & S_IFMT);
	   if (key == S_IFDIR)
	   		curr->isdir[i] = 1;
	   else
	   		curr->isdir[i]= 0;
	   if (dp->d_name[0] == '.')
		   curr->visible[i] = 0;
	   else
		   curr->visible[i] = 1;
		curr->list[i] = ft_strdup(dp->d_name);
		curr->size[i] = sb.st_size;
		curr->atim[i] = ft_strdup(ctime(&sb.st_atime));
		curr->mtim[i] = ft_strdup(ctime(&sb.st_mtime));
		curr->ctim[i] = ft_strdup(ctime(&sb.st_ctime));
		curr->permd[i] = ft_strdup(permstr(ft_itoa_base(sb.st_mode, 8), curr->isdir[i]));
		if (ft_strlen(dp->d_name) > curr->longest)
			curr->longest = ft_strlen(dp->d_name);
		i++;
	}
}

int checkinf(char *str)
{
	if ((ft_strcmp(str,".") == 0 ) || (ft_strcmp(str,"..") == 0))
		return (0);
	return(1);
}

//sorting
void add_sorted(h_dir **current, h_dir **newer, int n, int o)
{
	h_dir *new;
	h_dir *curr;

	curr = *current;
	new = *newer;
	new->list[n] = ft_strdup(curr->list[o]);
	free(curr->list[n]);
	curr->list[n] = NULL;
}

char	**dup_strarray(h_dir **current, char **list)
{
	char	**ret;
	int		x;

	ret = ft_memalloc(sizeof(char *) * (*current)->msize);
	x = -1;
	while (++x < (*current)->msize)
		ret[x] = ft_strdup(list[x]);
	return (ret);
}

int	name_sort(h_dir **current, int pos1, int pos2)
{
	h_dir *curr;

	curr = *current;
	return (ft_strcmp(curr->list[pos1], curr->list[pos2]) > 0);
}

void lex_sort(h_dir **current, int (*sort_func)(h_dir **, int, int))
{
	int		iterator;
	h_dir	*curr;
	int		min;
	int		pos_in_list;
	int		*found;

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

void upper_r(char *str)
{
	h_dir *curr;
	int i;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	lex_sort(&curr, name_sort);
	key = betterjoin("%-12s%-", (ft_itoa_base((curr->longest + 2), 10)));
	key = betterjoin(key, "s%s");
	i = 0;
	while(i < curr->msize)
	{
		ft_printf(key, curr->permd[curr->print[i]] ,curr->list[curr->print[i]], curr->ctim[curr->print[i]]);
		i++;
	}
	i = 0;
	while(i < curr->msize)
	{
		if(curr->list[curr->print[i]] && curr->visible[curr->print[i]] && curr->isdir[curr->print[i]]
			&& checkinf(curr->list[curr->print[i]]))
		{
			ft_printf("\n%s:\n", makepath(str, curr->list[curr->print[i]]));
			upper_r(makepath(str, curr->list[curr->print[i]]));
		}
	i++;
	}
}

int main()
{
    upper_r(".");
}
