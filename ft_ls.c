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
}

char* permstr(char *perm)
{
	perm = NULL;
	return("hello");
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
		   perror("fuckkkk");
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
		curr->permd[i] = ft_strdup(permstr(ft_itoa_base(sb.st_mode, 8)));
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

void lex_sort(h_dir **current, char **list)
{
	int		iterator;
	h_dir	*curr;
	char	*min;
	int		pos_in_list;
	char	**cpy;

	curr = *current;
	iterator = 0;
	cpy = dup_strarray(current, list);
	while (iterator < curr->msize)
	{
		min = 0;
		pos_in_list = 0;
		while (pos_in_list < curr->msize)
		{
			if (cpy[pos_in_list][0] && (min == 0 || ft_strcmp(min, cpy[pos_in_list]) > 0))
			{
				curr->print[iterator] = pos_in_list;
				min = cpy[pos_in_list];
			}
			pos_in_list++;
		}
		min[0] = 0;
		iterator++;
	}
}

// void lex_sort(h_dir **current, char **list)
// {
// 	int temp;
// 	int i;
// 	int z;
// 	h_dir *curr;
//
// 	i = 0;
// 	z = 0;
// 	curr = *current;
// 	while (z < curr->msize)
// 	{
// 		temp = 0;
// 		while (!list[i][0])
// 		{
// 			i++;
// 		}
// 		while (i < curr->msize)
// 		{
// 			while (!list[i])
// 				i++;
// 			if (ft_strcmp(list[temp], list[i]) < 0)
// 			{
// 				temp = i;
// 			}
// 			i++;
// 		}
// 		ft_putnbr(temp);
// 		ft_putendl("a");
// 		curr->print[z] = temp;
// 		list[temp] = ft_strdup("");
// 		i = 0;
// 		z++;
// 	}
// }
void upper_r(char *str)
{
	h_dir *curr;
	int i;
	//int *print;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	lex_sort(&curr, curr->list);
	i = 0;
	while(i < curr->msize)
	{
		ft_printf("%s\n", curr->list[curr->print[i]]);
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
