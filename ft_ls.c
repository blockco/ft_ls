#include "ft_ls.h"
#include <stdio.h>

char* denyname(char *str)
{
	int i;
	int a;
	char *ret;

	i = 2;
	a = 0;
	ret = malloc(ft_strlen(str) - 1);
	while(str[i])
	{
		ret[a] = str[i];
		i++;
		a++;
	}
	ret[a] = '\0';
	return ret;
}

int findmsize(char *str)
{
	int msize;
	DIR *dir;
	struct dirent *dp;

	msize = 0;
	errno = 0;
	dir = opendir (str);
	if (errno == EACCES)
	{
		ft_printf("%s\n%s%s%s\n\n", str, "ls: " , denyname(str) , ": Permission denied");
		return(0);
	}
	if (dir)
	{
		while ((dp = readdir (dir)) != NULL)
			msize++;
		closedir(dir);
	}
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
	curr->atim_s = (long long*)malloc(sizeof(long long) * curr->msize);
	curr->atim_n = (long*)malloc(sizeof(long) * curr->msize);

	curr->l_count = (char**)malloc(sizeof(char*) * curr->msize);

	curr->mtim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->mtim_s = (long long*)malloc(sizeof(long long) * curr->msize);
	curr->mtim_n = (long*)malloc(sizeof(long) * curr->msize);

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


	curr->blocks = 0;
	curr->longest = 0;
	curr->groupsize = 0;
	curr->sizeprint = 0;
	curr->ownersize = 0;
	curr->v_block = 0;
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

//get link
int getlnk(struct stat sb_l, h_dir **current, int i)
{
	struct passwd *pwuser;
	struct group *grpnam;
	h_dir *curr;
	curr = *current;

   if (NULL == (pwuser = getpwuid(sb_l.st_uid)))
	{
	   perror("getpwuid()");
	   exit(EXIT_FAILURE);
	}
	if (NULL == (grpnam = getgrgid(sb_l.st_gid)))
	{
		perror("getgrgid()");
		exit(EXIT_FAILURE);
	}
	if ((sb_l.st_mode & S_IFMT) == S_IFDIR)
		curr->isdir[i] = 1;
	else
		curr->isdir[i] = 0;
	if ((sb_l.st_mode & S_IFMT) == S_IFLNK)
		curr->islnk[i] = 1;
	else
		curr->islnk[i] = 0;
	if (curr->list[i][0] == '.')
		curr->visible[i] = 0;
	else
		curr->visible[i] = 1;
	curr->owner[i] = ft_strdup(pwuser->pw_name);
	curr->group[i] = ft_strdup(grpnam->gr_name);
	curr->size[i] = sb_l.st_size;
	curr->atim[i] = ft_strdup(ctime(&sb_l.st_atime));
	curr->atim_s[i] = (long long)sb_l.st_atimespec.tv_sec;
	curr->atim_n[i] = (long)sb_l.st_atimespec.tv_nsec;
	curr->mtim[i] = ft_strdup(ctime(&sb_l.st_mtime));
	curr->mtim_s[i] = (long long)sb_l.st_mtimespec.tv_sec;
	curr->mtim_n[i] = (long)sb_l.st_mtimespec.tv_nsec;
	curr->ctim[i] = ft_strdup(ctime(&sb_l.st_ctime));
	curr->time_v[i] = sb_l.st_mtime;
	curr->ctim_s[i] = (long long)sb_l.st_ctimespec.tv_sec;
	curr->ctim_n[i] = (long)sb_l.st_ctimespec.tv_nsec;
	curr->permd[i] = ft_strdup(permstr(ft_itoa_base(sb_l.st_mode, 8), curr->isdir[i]));
	curr->l_count[i] = ft_itoa_base(sb_l.st_nlink, 10);
	return(sb_l.st_blocks);
}

void initstruct(h_dir **current, char *str)
{
	DIR *dir;
	int temp;
	int i;
	struct dirent *dp;
	struct stat sb_l;
	h_dir *curr;
	long long block;

	block = 0;
	i = 0;
	curr = *current;
	mallocstruct(&curr);
	errno = 0;
	dir = opendir(str);
	if (errno == EACCES)
		return;
	while ((dp = readdir (dir)) != NULL)
	{
		if (-1 == lstat(makepath(str, dp->d_name), &sb_l))
		{
			perror("name overload");
			exit(EXIT_FAILURE);
		}
		curr->list[i] = ft_strdup(dp->d_name);
		temp = getlnk(sb_l, &curr, i);
		block += temp;
		if (curr->visible[i] == 0)
		{
			curr->v_block += temp;
		}
		i++;
	}
	closedir(dir);
	curr->blocks = block;
}

int checkinf(char *str)
{
	if ((ft_strcmp(str,".") == 0 ) || (ft_strcmp(str,"..") == 0) )
		return (0);
	return(1);
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

int time_sort(h_dir **current, int pos1, int pos2)
{
	h_dir *curr;

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

void findmax(h_dir **current)
{
	int i;
	h_dir *curr;

	i = 0;
	curr = *current;
	while (curr->list[i])
	{
		if (ft_strlen(curr->l_count[i]) > curr->linksize)
			curr->linksize = ft_strlen(curr->l_count[i]);
		if (ft_strlen(curr->list[i]) > curr->longest)
			curr->longest = ft_strlen(curr->list[i]);
		if (ft_strlen(curr->owner[i]) > curr->ownersize)
			curr->ownersize = ft_strlen(curr->owner[i]);
		if (ft_strlen(ft_itoa_base(curr->size[i], 10)) > curr->sizeprint)
			curr->sizeprint = ft_strlen(ft_itoa_base(curr->size[i], 10));
		if (ft_strlen(curr->group[i]) > curr->groupsize)
			curr->groupsize = ft_strlen(curr->group[i]);
		i++;
	}
}

void timefix(char *time_s)
{
	time_s = ft_strsub(time_s, 5, (ft_strlen(time_s) - 5));
}

void trimtime(char *time_s)
{
	time_s[ft_strlen(time_s) - 1] = 0;
	timefix(time_s);
}

char *printlnk(char *str)
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

char* makekey(h_dir **current)
{
	char	*key;
	h_dir *curr;

	curr = *current;
	key = betterjoin("%-12s%-", (ft_itoa_base((curr->linksize), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, (ft_itoa_base((curr->ownersize + 2), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, ft_itoa_base((curr->groupsize + 2), 10));
	key = betterjoin(key,"s%-");
	key = betterjoin(key, ft_itoa_base((curr->sizeprint + 1), 10));
	key = betterjoin(key, "s%-13");
	key = betterjoin(key, "s%-");
	key = betterjoin(key, ft_itoa_base((curr->longest + 2), 10));
	key = betterjoin(key, "s");
	return key;
}

void initflag(t_opt *flags)
{
	flags->l_op = 0;
	flags->reg_ls = 0;
	flags->rec_op = 0;
	flags->a_op = 0;
	flags->rev_op = 0;
	flags->t_op = 0;
}

void checkflag(char c, t_opt *flags)
{
	if (c == 'l')
		flags->l_op = 1;
	else if (c == 'R')
		flags->rec_op = 1;
	else if (c == 'a')
		flags->a_op = 1;
	else if (c == 'r')
		flags->rev_op = 1;
	else if (c == 't')
		flags->t_op = 1;
}

char *parseinput(const char **input, t_opt *flags, int argc)
{
	int i;
	int c;

	i = 1;
	while (i < argc)
	{
		c = 0;
		while(input[i][c])
			checkflag(input[i][c++], flags);
		i++;
	}
	if (input[argc - 1][0] != '-')
		return(ft_strdup(input[argc - 1]));
	else
		return (ft_strdup("."));
}

void printflags(t_opt *flags)
{
	ft_printf("%d\n%d\n%d\n%d\n%d\n%d\n", flags->l_op,flags->reg_ls,flags->rec_op,flags->a_op,flags->rev_op,flags->t_op);
}

void upper_rl(char *str, int first)
{
	h_dir *curr;
	int i;
	char* temp;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	lex_sort(&curr, time_sort);
	key = makekey(&curr);

	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
		{
			temp = makepath(str, curr->list[curr->print[i]]);
			temp[ft_strlen(temp) - 1] = '\0';
		if (first++)
			ft_printf("\n%s:\n", temp);
		ft_printf("%s%lld\n", "total ",curr->blocks);
		}
		trimtime(curr->mtim[curr->print[i]]);
		ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]],
		ft_itoa_base(curr->size[curr->print[i]], 10), curr->list[curr->print[i]], curr->mtim[curr->print[i]]);
		if (curr->islnk[curr->print[i]])
			ft_printf("%s%s\n", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
		else
			ft_putchar('\n');
		i++;
	}
	i = 0;
	while(i < curr->msize)
	{
		if(curr->list[curr->print[i]] && curr->isdir[curr->print[i]]
			&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		{
			upper_rl(makepath(str, curr->list[curr->print[i]]), first);
		}
	i++;
	}
}

char* settime(char *str)
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
	return ret;
}


void ls_l(char *str)
{
	h_dir *curr;
	int i;
	char* temp;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	lex_sort(&curr, name_sort);
	key = makekey(&curr);

	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
		{
			temp = makepath(str, curr->list[curr->print[i]]);
			temp[ft_strlen(temp) - 1] = '\0';
			ft_printf("%s%lld\n", "total ",(curr->blocks - curr->v_block));
		}
		trimtime(curr->mtim[curr->print[i]]);
		if (curr->visible[curr->print[i]])
		{
			ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]],
			ft_itoa_base(curr->size[curr->print[i]], 10), settime(curr->mtim[curr->print[i]]), curr->list[curr->print[i]]);
		}
		if (curr->islnk[curr->print[i]])
			ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
		if (curr->visible[curr->print[i]])
			ft_putchar('\n');
		i++;
	}
}

void ls_la(char *str)
{
	h_dir *curr;
	int i;
	char* temp;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	lex_sort(&curr, name_sort);
	key = makekey(&curr);
	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
		{
			temp = makepath(str, curr->list[curr->print[i]]);
			temp[ft_strlen(temp) - 1] = '\0';
			ft_printf("%s%lld\n", "total ",(curr->blocks));
		}
		trimtime(curr->mtim[curr->print[i]]);
		ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]],
		ft_itoa_base(curr->size[curr->print[i]], 10), settime(curr->mtim[curr->print[i]]), curr->list[curr->print[i]]);
		if (curr->islnk[curr->print[i]])
			ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
		else
			ft_putchar('\n');
		i++;
	}
}

void ls_lta(char *str)
{
	h_dir *curr;
	int i;
	char* temp;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	lex_sort(&curr, time_sort);
	key = makekey(&curr);
	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
		{
			temp = makepath(str, curr->list[curr->print[i]]);
			temp[ft_strlen(temp) - 1] = '\0';
			ft_printf("%s%lld\n", "total ",(curr->blocks));
		}
		trimtime(curr->mtim[curr->print[i]]);
		ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]],
		ft_itoa_base(curr->size[curr->print[i]], 10), settime(curr->mtim[curr->print[i]]), curr->list[curr->print[i]]);
		if (curr->islnk[curr->print[i]])
			ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
		else
			ft_putchar('\n');
		i++;
	}
}

void dispatchls(t_opt *flags, char *str)
{
	if (flags->l_op && flags->a_op && flags->t_op)
		ls_lta(str);
	else if (flags->l_op && flags->a_op)
		ls_la(str);
	else if (flags->l_op)
		ls_l(str);
}

int main(int argc, char const *argv[])
{
	t_opt *flags;
	char *str;
	flags = malloc(sizeof(t_opt));
	initflag(flags);
	if (argc > 1)
		str = parseinput(argv, flags, argc);
	else
		str = ft_strdup(".");
	dispatchls(flags, str);
	//upper_rl(str, 0);
}
