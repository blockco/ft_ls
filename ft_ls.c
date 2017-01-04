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

void normprint(char *str)
{
	h_dir *curr;
	int i;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	i = 0;
	while(curr->list[i])
	{
		ft_printf("%s\n", curr->list[i]);
		i++;
	}
	i = 0;
	while(curr->list[i])
	{
		// ft_printf("%s\n\n", curr->list[i]);
		// ft_printf("isdir:%d\n", curr->isdir[i]);
		// ft_printf("isvis:%d\n", curr->visible[i]);
		// ft_printf("isinf:%d\n", checkinf(curr->list[i]));
		// ft_putendl("----------------");
		if(curr->list[i] && curr->visible[i] && curr->isdir[i]
			&& checkinf(curr->list[i]))
		{
			ft_putendl("---------");
			normprint(makepath(str, curr->list[i]));
		}
	i++;
	}
}

int main()
{
    normprint(".");
}
