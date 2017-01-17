#include "ft_ls.h"

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
	curr->isblock = (int*)malloc(sizeof(int) * curr->msize);
	curr->block_dev = (long*)malloc(sizeof(long) * curr->msize);
	curr->block_min = (long*)malloc(sizeof(long) * curr->msize);


	curr->blocks = 0;
	curr->longest = 0;
	curr->groupsize = 0;
	curr->sizeprint = 0;
	curr->ownersize = 0;
	curr->v_block = 0;
}

char* intit_perm(int isdir, int islnk)
{
	if (isdir)
		return(ft_strdup("d"));
	else if (islnk)
		return(ft_strdup("l"));
	return(ft_strdup("-"));
}

char* permstr(char *perm, int isdir, int isdev, int islnk)
{
	int i;
	char *ret;
	if (isdir)
		i = 2;
	else
		i = 3;
	ret = intit_perm(isdir, islnk);
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
	if (isdev)
		ret = betterjoin("crw", ret);
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
	if ((sb_l.st_mode & S_IFMT) == S_IFBLK || (sb_l.st_mode & S_IFMT) == S_IFCHR)
	{
		curr->isblock[i] = 1;
		curr->block_min[i] = minor(sb_l.st_rdev);
		curr->hasblock = 1;
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
	curr->block_dev[i] = major(sb_l.st_rdev);
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
	curr->permd[i] = ft_strdup(permstr(ft_itoa_base(sb_l.st_mode, 8), curr->isdir[i], curr->isblock[i], curr->islnk[i]));
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

		if (ft_strlen(ft_itoa_base(curr->block_dev[i], 10)) > curr->sizeprint)
			curr->sizeprint = ft_strlen(ft_itoa_base(curr->block_dev[i], 10));

		if (ft_strlen(curr->group[i]) > curr->groupsize)
			curr->groupsize = ft_strlen(curr->group[i]);

		if (ft_strlen(ft_itoa_base(curr->block_min[i], 10)) > curr->ran)
			curr->ran = ft_strlen(ft_itoa_base(curr->block_min[i], 10));
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
	int i;

	i = 0;
	curr = *current;
	if (curr->linksize > 10)
		i = 1;
	key = betterjoin("%-12s%-", (ft_itoa_base((curr->linksize + 1), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, (ft_itoa_base((curr->ownersize + 2), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, ft_itoa_base((curr->groupsize + 2), 10));
	key =betterjoin(key, "s");
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

void printflags(t_opt *flags)
{
	ft_printf("%d\n%d\n%d\n%d\n%d\n%d\n", flags->l_op,flags->reg_ls,flags->rec_op,flags->a_op,flags->rev_op,flags->t_op);
}

char *parseinput(const char **input, t_opt *flags, int argc)
{
	int i;
	int c;
	char *str;

	i = 1;
	if (input[1][0] == '-')
		str = ft_strdup(".");
	else
	{
		str = ft_strdup(input[1]);
		i++;
	}
	while (i < argc && (input[i][0] == '-'))
	{
		c = 0;
		while(input[i][c])
			checkflag(input[i][c++], flags);
		i++;
	}
	return str;
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

char* normkey(h_dir *curr)
{
	char *ret;
	ret = betterjoin("%-", ft_itoa_base((curr->longest + 1), 10));
	ret = betterjoin(ret, "s");
	return (ret);
}

// void ls_norm(char *str)
// {
// 	h_dir *curr;
// 	int i;
// 	int write;
// 	char *key;
//
// 	curr = malloc(sizeof(h_dir));
// 	curr->msize = findmsize(str);
// 	initstruct(&curr, str);
// 	findmax(&curr);
// 	lex_sort(&curr, name_sort);
// 	key = normkey(curr);
// 	i = 0;
// 	write = 0;
// 	while(i < curr->msize)
// 	{
// 		if (curr->visible[curr->print[i]])
// 		{
// 			ft_printf(key, curr->list[curr->print[i]]);
// 			write += curr->longest + 1;
// 		}
// 		if (write >= 50)
// 		{
// 			ft_putchar('\n');
// 			write = 0;
// 		}
// 		i++;
// 	}
// }

void makevisible(h_dir *curr)
{
	int i;

	i = 0;
	while (i < curr->msize)
	{
		curr->visible[i] = 1;
		i++;
	}
}

void handle_op(h_dir *curr, t_opt *flags)
{
	if (flags->a_op)
		makevisible(curr);
}

void revprint(h_dir *curr)
{
	int temp;

	temp = curr->msize;
	temp--;
	while(temp > -1)
	{
		if (curr->visible[curr->print[temp]])
			ft_printf("%s\n", curr->list[curr->print[temp]]);
		temp--;
	}
}

void normprint(h_dir *curr)
{
	int i;

	i = 0;
	while(i < curr->msize)
	{
		if (curr->visible[curr->print[i]])
			ft_printf("%s\n", curr->list[curr->print[i]]);
		i++;
	}
}

void ls_norm(char *str, t_opt *flags, int first)
{
	h_dir *curr;
	int i;
	char *key;
	char *temp;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op(curr ,flags);
	key = normkey(curr);
	temp = makepath(str, curr->list[curr->print[0]]);
	temp[ft_strlen(temp) - 1] = '\0';
	if (first++)
		ft_printf("\n%s:\n", temp);
	if (flags->rev_op)
		revprint(curr);
	else
		normprint(curr);
	i = 0;
	while(i < curr->msize && flags->rec_op)
	{
		if(curr->list[curr->print[i]] && curr->visible[curr->print[i]] &&curr->isdir[curr->print[i]]
			&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		{
			ls_norm(makepath(str, curr->list[curr->print[i]]), flags, first);
		}
	i++;
	}
}

void revprint_l(h_dir *curr, char *str)
{
	int temp;

	temp = curr->msize;
	temp--;
	while(temp > -1)
	{
		if (curr->visible[curr->print[temp]])
		{
			ft_printf(makekey(&curr), curr->permd[curr->print[temp]], curr->l_count[curr->print[temp]] ,curr->owner[curr->print[temp]], curr->group[curr->print[temp]],
			ft_itoa_base(curr->size[curr->print[temp]], 10), settime(curr->mtim[curr->print[temp]]), curr->list[curr->print[temp]]);
			if (curr->islnk[curr->print[temp]])
				ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[temp]])));
			if (curr->visible[curr->print[temp]])
				ft_putchar('\n');
		}
		temp--;
	}
}

void normprint_l(h_dir *curr, char *str)
{
	int i;

	i = 0;
	while(i < curr->msize)
	{
		if (curr->visible[curr->print[i]])
		{
			ft_printf(makekey(&curr), curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]],
			ft_itoa_base(curr->size[curr->print[i]], 10), settime(curr->mtim[curr->print[i]]), curr->list[curr->print[i]]);
			if (curr->islnk[curr->print[i]])
				ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
			if (curr->visible[curr->print[i]])
				ft_putchar('\n');
		}
		i++;
	}
}

void lsdiff(char *str, t_opt *flags, int first)
{
	h_dir *curr;
	int i;
	char *temp;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op(curr ,flags);
	temp = makepath(str, curr->list[curr->print[0]]);
	temp[ft_strlen(temp) - 1] = '\0';
	if (first++)
		ft_printf("\n%s:\n", temp);
	if (flags->rev_op)
		revprint_l(curr, str);
	else
		normprint_l(curr, str);
	i = 0;
	while(i < curr->msize && flags->rec_op)
	{
		if(curr->list[curr->print[i]] && curr->visible[curr->print[i]] &&curr->isdir[curr->print[i]]
			&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		{
			lsdiff(makepath(str, curr->list[curr->print[i]]), flags, first);
		}
	i++;
	}
}

void makerev(h_dir *curr)
{
	int i;
	int *ret;
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

void handle_op_l(h_dir *curr, t_opt *flags)
{
	if (flags->a_op)
		makevisible(curr);
	if (flags->rev_op)
		makerev(curr);
}

void printrest(h_dir *curr, int i)
{
	char *key;

	key = ft_strdup("%s%s%s%s%s%s%-13s%-0s");
	if (curr->isblock[i])
	{
		ft_printf(key, makespace(curr->sizeprint - ft_strlen(ft_itoa_base(curr->block_dev[i] + 1, 10)), ' '),
		ft_itoa_base(curr->block_dev[i], 10), ",", makespace((curr->ran - ft_strlen(ft_itoa_base(curr->block_min[i], 10)) + 1), ' '), ft_itoa_base(curr->block_min[i], 10),  " ",settime(curr->mtim[i]), curr->list[i],
		curr->list[i]);
		return;
	}
	if (curr->hasblock)
	{
		ft_printf("%s", makespace((curr->ran + 2), ' '));
	}
	key = ft_strdup("%s%s%s%-13s%-0s");
	ft_printf(key, makespace(curr->sizeprint - ft_strlen(ft_itoa_base(curr->size[i], 10)), ' '),
	ft_itoa_base(curr->size[i], 10), " ", settime(curr->mtim[i]), curr->list[i]);
}

void upper_rl(char *str, int first, t_opt *flags)
{
	h_dir *curr;
	int i;
	char *key;

	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	initstruct(&curr, str);
	findmax(&curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op_l(curr, flags);
	key = makekey(&curr);
	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
		{
		if (first++)
			ft_printf("\n%s:\n", str);
		if (flags->a_op)
			curr->v_block = 0;
		ft_printf("%s%lld\n", "total ",(curr->blocks - curr->v_block));
		}
		if (curr->visible[curr->print[i]])
		{
			trimtime(curr->mtim[curr->print[i]]);
			ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]]);
			printrest(curr, curr->print[i]);
			if (curr->islnk[curr->print[i]])
				ft_printf("%s%s\n", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
			else
				ft_putchar('\n');
		}
		i++;
	}
	i = 0;
	while(i < curr->msize && flags->rec_op)
	{
		if(curr->list[curr->print[i]] && curr->visible[curr->print[i]]&& curr->isdir[curr->print[i]]
			&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		{
			upper_rl(makepath(str, curr->list[curr->print[i]]), first, flags);
		}
	i++;
	}
}

void dispatchls(t_opt *flags, char *str)
{
	if (!flags->l_op)
		ls_norm(str, flags, 0);
	else
		upper_rl(str, 0, flags);
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
}
