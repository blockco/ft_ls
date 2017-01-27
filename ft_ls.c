
#include "ft_ls.h"

void timefix(char *time_s)
{
	time_s = ft_strsub(time_s, 5, (ft_strlen(time_s) - 5));
}

void trimtime(char *time_s)
{
	time_s[ft_strlen(time_s) - 1] = 0;
	timefix(time_s);
}

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
		ft_printf("%s:\n%s%s%s\n", str, "ls: " , denyname(str) , ": Permission denied");
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

void mallocrest(h_dir **current)
{
	h_dir *curr;

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

void mallocstruct(h_dir **current)
{
	h_dir *curr;

	curr = *current;
	curr->list = (char**)malloc(sizeof(char*) * curr->msize + 1);
	curr->list[curr->msize] = NULL;
	curr->isdir = (int*)malloc(sizeof(int) * curr->msize);
	curr->old = (int*)malloc(sizeof(int) * curr->msize);
	curr->size = (long*)malloc(sizeof(long) * curr->msize);
	curr->year = (char**)malloc(sizeof(char*) * curr->msize);
	curr->atim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->atim_s = (long long*)malloc(sizeof(long long) * curr->msize);
	curr->atim_n = (long*)malloc(sizeof(long) * curr->msize);
	curr->l_count = (char**)malloc(sizeof(char*) * curr->msize);
	curr->mtim = (char**)malloc(sizeof(char*) * curr->msize);
	curr->mtim_s = (long long*)malloc(sizeof(long long) * curr->msize);
	curr->mtim_n = (long*)malloc(sizeof(long) * curr->msize);
	curr->blocks = 0;
	curr->longest = 0;
	curr->groupsize = 0;
	curr->sizeprint = 0;
	curr->ownersize = 0;
	curr->v_block = 0;
	mallocrest(&curr);
}

char* intit_perm(int isdir, int islnk)
{
	if (isdir)
		return(ft_strdup("d"));
	else if (islnk)
		return(ft_strdup("l"));
	return(ft_strdup("-"));
}

char *findperm(char c)
{
	if(c == '7')
		return (ft_strdup("rwx"));
	else if (c == '6')
		return (ft_strdup("rw-"));
	else if (c == '5')
		return (ft_strdup("r-x"));
	else if (c == '4')
		return (ft_strdup("r--"));
	else if (c == '3')
		return (ft_strdup("-wx"));
	else if (c == '2')
		return (ft_strdup("-w-"));
	else if (c == '1')
		return (ft_strdup("--x"));
	else
		return (ft_strdup("---"));
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
		ret = betterjoin(ret,findperm(perm[i]));
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

char* getyear(char *str)
{
	int i;
	char *ret;
	int a;

	ret = ft_strnew(4);
	i = ft_strlen(str) - 5;
	a = 0;
	while (str[i])
	{
		ret[a] = str[i];
		a++;
		i++;
	}
	return ret;
}

//get link
void morelink(struct stat sb_l, h_dir *curr, int i)
{
	static time_t now;

	now = time(NULL);
	curr->size[i] = sb_l.st_size;
	curr->block_dev[i] = major(sb_l.st_rdev);
	curr->atim[i] = ft_strdup(ctime(&sb_l.st_atime));
	curr->atim_s[i] = (long long)sb_l.st_atimespec.tv_sec;
	curr->atim_n[i] = (long)sb_l.st_atimespec.tv_nsec;
	curr->mtim[i] = ft_strdup(ctime(&sb_l.st_mtime));
	curr->year[i] = getyear(curr->mtim[i]);
	curr->mtim_s[i] = (long long)sb_l.st_mtimespec.tv_sec;
	curr->mtim_n[i] = (long)sb_l.st_mtimespec.tv_nsec;
	curr->ctim[i] = ft_strdup(ctime(&sb_l.st_ctime));
	curr->time_v[i] = sb_l.st_mtime;
	curr->ctim_s[i] = (long long)sb_l.st_ctimespec.tv_sec;
	curr->ctim_n[i] = (long)sb_l.st_ctimespec.tv_nsec;
	curr->permd[i] = ft_strdup(permstr(ft_itoa_base(sb_l.st_mode, 8), curr->isdir[i], curr->isblock[i], curr->islnk[i]));
	curr->l_count[i] = ft_itoa_base(sb_l.st_nlink, 10);
	if(sb_l.st_mtime + SIXMONTHS > now && sb_l.st_mtime < now + SIXMONTHS)
		curr->old[i] = 0;
	else
		curr->old[i] = 1;
}

void evenmorelnk(struct stat sb_l, h_dir *curr, int i)
{
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
	morelink(sb_l, curr, i);
}

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
	evenmorelnk(sb_l, curr, i);
	curr->owner[i] = ft_strdup(pwuser->pw_name);
	curr->group[i] = ft_strdup(grpnam->gr_name);
	return(sb_l.st_blocks);
}

void initial(h_dir **current, char **str)
{
	int temp;
	int i;
	struct stat sb_l;
	h_dir *curr;
	long long block;

	block = 0;
	i = 0;
	curr = *current;
	mallocstruct(&curr);
	errno = 0;
	if (errno == EACCES)
		return;
	while (str[i] != NULL)
	{
		if (-1 == lstat(makepath(".", str[i]), &sb_l))
		{
			ft_putstr("ls: ");
			perror(str[i]);
			exit(EXIT_FAILURE);
		}
		curr->list[i] = ft_strdup(str[i]);
		temp = getlnk(sb_l, &curr, i);
		block += temp;
		if (curr->visible[i] == 0)
		{
			curr->v_block += temp;
		}
		i++;
	}
	curr->blocks = block;
}

void initstruct(h_dir *curr, char *str, int i)
{
	DIR *dir;
	int temp;
	struct dirent *dp;
	struct stat sb_l;

	curr->blocks = 0;
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
		curr->blocks += temp;
		if (curr->visible[i++] == 0)
			curr->v_block += temp;
	}
	closedir(dir);
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

void findmax(h_dir *curr)
{
	int i;

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
	key = betterjoin("%-12s%-", (ft_itoa_base((curr->linksize + 1), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, (ft_itoa_base((curr->ownersize + 2), 10)));
	key = betterjoin(key, "s%-");
	key = betterjoin(key, ft_itoa_base((curr->groupsize + 2), 10));
	key =betterjoin(key, "s");
	return key;
}

void initflag(t_opt *flags, int *i, int *d_size)
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

void noz(char c)
{
	char *str;
	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	ft_printf("ls: illegal option -- %c\n", c);
	ft_putendl("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
	exit(1);
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
	else if (c == 'Z' || c == 'z' || c == '-')
		noz(c);
}

void printflags(t_opt *flags)
{
	ft_printf("%d\n%d\n%d\n%d\n%d\n%d\n", flags->l_op,flags->reg_ls,flags->rec_op,flags->a_op,flags->rev_op,flags->t_op);
}

int moreparse(int i, int c, const char **input, t_opt *flags)
{
	while(input[i][c])
	{
		if (input[i][c] == '-')
			c++;
		checkflag(input[i][c++], flags);
	}
	return c;
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
		if (ft_strcmp("--", input[i]) == 0)
			break;
		if (input[i][c] == '-' && (input[i][c + 1]))
			c = moreparse(i, c, input, flags);
		i++;
	}
	return str;
}

char* normkey(h_dir *curr)
{
	char *ret;
	ret = betterjoin("%-", ft_itoa_base((curr->longest + 1), 10));
	ret = betterjoin(ret, "s");
	return (ret);
}

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


char *quickdirchange(char *str)
{
	char *ret;

	ret = ft_strdup(str);
	//ret[ft_strlen(str) - 2] = '\0';
	return ret;
}

void morenorm(h_dir *curr, char *str, t_opt *flags)
{
	initstruct(curr, str, 0);
	findmax(curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op(curr ,flags);
}

int morestuff(int first, char *str, t_opt *flags, h_dir *curr)
{
	if (first++)
		ft_printf("%s:\n", str);
	if (flags->rev_op)
		revprint(curr);
	else
		normprint(curr);
	return (first);
}

int checkifnorm(h_dir *curr, int i)
{
	if (curr->list[curr->print[i]] && curr->visible[curr->print[i]]
		&&curr->isdir[curr->print[i]]
		&& checkinf(curr->list[curr->print[i]]) &&
		!curr->islnk[curr->print[i]])
		return (1);
	return 0;
}

void dosome(int first)
{
	if (first > 0)
		ft_printf("\n");
}

void moresome(int *i, int *inc, t_opt *flags, h_dir *curr)
{
	if (flags->rev_op)
		*i = curr->msize - 1;
	else
		*inc = 1;
}

void ls_norm(char *str, t_opt *flags, int first)
{
	h_dir *curr;
	int i;
	char *temp;
	int inc;

	inc = -1;
	i = 0;
	curr = malloc(sizeof(h_dir));
	curr->msize = findmsize(str);
	if (curr->msize == 0)
		return;
	morenorm(curr, str, flags);
	temp = makepath(str, curr->list[curr->print[0]]);
	temp[ft_strlen(temp) - 2] = '\0';
	first = morestuff(first, str, flags, curr);
	moresome(&i, &inc, flags, curr);
	while(i > -1 && i < curr->msize && flags->rec_op)
	{
		if(checkifnorm(curr, i))
		{
			dosome(first);
			ls_norm(makepath(str, curr->list[curr->print[i]]), flags, first);
		}
	i = i + inc;
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

char *yearswitch(char *str, char *year)
{
	int i;
	char *ret;
	char *c;

	c = ft_strchr(year,'\n');
	c[0] = 0;
	ret = ft_strnew(7);
	i = 0;
	while(i < 7)
	{
		ret[i] = str[i];
		i++;
	}
	ret = betterjoin(ret," ");
	return(betterjoin(ret, year));

}

char* settime(char *str, int old, char *year)
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
	return ret;
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
			ft_itoa_base(curr->size[curr->print[temp]], 10), settime(curr->mtim[curr->print[temp]],curr->old[curr->print[temp]], curr->year[curr->print[temp]]), curr->list[curr->print[temp]]);
			if (curr->islnk[curr->print[temp]])
				ft_printf("%s%s", " -> ", printlnk(makepath(str, curr->list[curr->print[temp]])));
			if (curr->visible[curr->print[temp]])
				ft_putchar('\n');
		}
		temp--;
	}
}

void printrest(h_dir *curr, int i)
{
	char *key;

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

int moreupperl(int first, char *str, h_dir *curr, t_opt *flags)
{
	if (first++)
		ft_printf("\n%s:\n", quickdirchange(str));
	if (flags->a_op)
		curr->v_block = 0;
	if (curr->blocks - curr->v_block > -1)
		ft_printf("%s%lld\n", "total ",(curr->blocks - curr->v_block));
	return first;
}

void evenupperr(char *key, h_dir *curr, int i, char *str)
{
	ft_printf(key, curr->permd[curr->print[i]], curr->l_count[curr->print[i]] ,curr->owner[curr->print[i]], curr->group[curr->print[i]]);
	printrest(curr, curr->print[i]);
	if (curr->islnk[curr->print[i]])
		ft_printf("%s%s\n", " -> ", printlnk(makepath(str, curr->list[curr->print[i]])));
	else
		ft_putchar('\n');
}

int uppertest(h_dir *curr, int i)
{
	if (curr->list[curr->print[i]] && curr->visible[curr->print[i]]&& curr->isdir[curr->print[i]]
		&& checkinf(curr->list[curr->print[i]]) && !curr->islnk[curr->print[i]])
		return 1;
	return 0;
}

void structstuff(h_dir *curr, char *str, t_opt *flags)
{
	curr->msize = findmsize(str);
	initstruct(curr, str, 0);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op_l(curr, flags);
	findmax(curr);
}
void upper_rl(char *str, int first, t_opt *flags)
{
	h_dir *curr;
	int i;
	char *key;

	curr = malloc(sizeof(h_dir));
	structstuff(curr, str, flags);
	key = makekey(&curr);
	i = 0;
	while(i < curr->msize)
	{
		if (i == 0)
			first = moreupperl(first, str, curr, flags);
		if (curr->visible[curr->print[i]])
			evenupperr(key, curr, i, str);
		i++;
	}
	i = 0;
	while(i < curr->msize && flags->rec_op)
	{
		if(uppertest(curr, i))
			upper_rl(makepath(str, curr->list[curr->print[i]]), first, flags);
	i++;
	}
	free(key);
	free(curr);
}

int arraysize(char** ret)
{
	int i;

	i = 0;
	while (ret[i] != NULL)
		i++;
	return (i);
}

int lhelp(int i, int inc, char **dir, int d_num)
{
	i = i + inc;
	if (d_num > 1 && (i > -1 && i < arraysize(dir)))
		ft_putendl("");
	return i;
}

int mhelp(int i, int inc, char **dir, int d_num)
{
	i = i + inc;
	if (d_num > 1 && (i > -1 && i < arraysize(dir)))
		ft_putendl("");
	return i;
}

void handlerev(t_opt *flags, int *i, int *inc, int d_num)
{
	if (flags->rev_op)
	{
		*i = d_num - 1;
		*inc = -1;
	}
	else
	{
		*i = 0;
		*inc = 1;
	}
}

void dispatchls(t_opt *flags, char **dir, int d_num)
{
	int i;
	int inc;

	handlerev(flags, &i, &inc, d_num);
	if (!flags->l_op)
	{
		while (i > -1 && i < arraysize(dir))
		{
			if (d_num > 1 && dir[i])
				ft_putendl(betterjoin(dir[i], ":"));
			ls_norm(dir[i], flags, 0);
			i = lhelp(i, inc, dir, d_num);
		}
	}
	else
	{
		while (i > -1 && i < d_num && dir[i])
		{
			if (d_num > 1 && dir[i])
				ft_putendl(betterjoin(dir[i], ":"));
			upper_rl(dir[i], 0, flags);
			i = mhelp(i, inc, dir, d_num);
		}
	}
}

int shelp(const char **argv, int count, char **ret, int i)
{
		malloc(0);
		ret[count] = ft_strdup(argv[i]);
		count = count + 1;
		return count;
}

int retit(const char **argv, int i, int *count)
{
	if (argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1]))
		*count = *count + 1;
	i++;
	return i;
}

void intitthem(int *opend, int *i, int *count)
{
	*opend = 0;
	*i = 1;
	*count = 0;
}

int easyc(int *opend, int i)
{
	*opend = 1;
	i++;
	return i;
}

char **storedirs(const char **argv, int *count)
{
	int i;
	char **ret;
	int opend;

	intitthem(&opend, &i, count);
	while(argv[i])
		i = retit(argv, i, count);
	ret = (char**)malloc(sizeof(char*) * *count + 1);
	*count = 0;
	i = 1;
	while(argv[i])
	{
		if (ft_strcmp("--", argv[i]) == 0 && !opend)
			 i = easyc(&opend, i);
		if (!argv[i])
			break;
		if ((argv[i][0] != '-') || opend || (argv[i][0] == '-' && !argv[i][1]))
		{
			*count = shelp(argv, *count, ret, i);
			opend = 1;
		}
		i++;
	}
	ret[*count] = NULL;
	return ret;
}

int founddir(char **dirs, int found, int i)
{
	ft_putstr("ls: ");
	perror(dirs[i]);
	found = 1;
	return found;
}

void setthem(int *a, int *i, int *b, int *found)
{
	*a = 0;
	*i = 0;
	*b = 0;
	*found = 0;
}

int seti(int i, char **dirs, DIR *dir)
{
	if (errno != 2 && !dirs[i])
		closedir(dir);
	i++;
	return i;
}

void makenull(int a, int b, char **ret, char **temp)
{
	ret[a] = NULL;
	temp[b] = NULL;
}

void lastexist(h_dir *curr, int d_size, char **ret)
{
	curr->list = (char**)malloc(sizeof(char*) * d_size + 1);
	ret[d_size] = NULL;
}
char **checkexist(char **dirs, int d_size, h_dir *curr, t_opt *flags)
{
	char **ret;
	DIR *dir;
	int i;
	int a;
	int b;
	int found;

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
	return(ret); //fix
}

void mainops(t_opt *flags, h_dir *curr, int *i, int *inc)
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

int checkinc(t_opt *flags, h_dir *curr)
{
	if (flags->rev_op && (!flags->rec_op && curr->msize > 0))
		return(-1);
	else
		return(1);
}


void mainprint(t_opt *flags, char *key, int i, h_dir *curr)
{
	int inc;

	inc = checkinc(flags, curr);
	while (i < curr->msize)
	{
		if (flags->l_op)
		{
			ft_printf(key, curr->permd[curr->print[i]],
				curr->l_count[curr->print[i]],
				curr->owner[curr->print[i]], curr->group[curr->print[i]]);
			printrest(curr, curr->print[i]);
			if (curr->islnk[curr->print[i]])
				ft_printf("%s%s\n", " -> ",
				printlnk(makepath(".", curr->list[curr->print[i]])));
			else
				ft_putchar('\n');
		}
		else if (flags->t_op)
			ft_putendl(curr->list[curr->print[i]]);
		else
			ft_putendl(curr->list[curr->print[i]]);
		i = i + inc;
		if (!curr->list[i])
			break;
	}
}

char *fixmain(h_dir *curr, t_opt *flags)
{
	char **temp;

	temp = curr->list;
	curr->msize = arraysize(temp);
	initial(&curr, temp);
	findmax(curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	return(makekey(&curr));
}

char **fixdir(char **dirs, int *d_size)
{
	dirs = (char**)malloc(sizeof(char*) * 2);
	dirs[0] = ft_strdup(".");
	dirs[1] = NULL;
	*d_size = 1;
	return dirs;
}

char **finishmain(int argc, char **dirs, int *d_size, const char **argv)
{
	if (argc > 1)
	{
		dirs = storedirs(argv, d_size);
		return (dirs);
	}
	return (NULL);
}

void flagfix(int argc, const char **argv, t_opt *flags)
{
	if (argc > 1)
		parseinput(argv, flags, argc);
}

void endl(t_opt *flags, int d_size, h_dir *curr)
{
	if ((flags->t_op || flags->rec_op) && (d_size > 0 && curr->msize > 1))
		ft_putendl("");
}

void freedub(char **data)
{
	int i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void moredirfree(h_dir *curr)
{
	free(curr->isblock);
	free(curr->block_dev);
	free(curr->block_min);
	free(curr->print);
	free(curr->islnk);
	free(curr);
}
void freedir(h_dir *curr)
{
	free(curr->savetime);
	free(curr->old);
	freedub(curr->year);
	freedub(curr->l_count);
	freedub(curr->owner);
	freedub(curr->list);
	free(curr->isdir);
	free(curr->size);
	free(curr->time_v);
	freedub(curr->atim);
	free(curr->atim_s);
	free(curr->atim_n);
	freedub(curr->mtim);
	free(curr->mtim_s);
	free(curr->mtim_n);
	free(curr->t_value);
	freedub(curr->ctim);
	free(curr->ctim_s);
	free(curr->ctim_n);
	freedub(curr->permd);
	freedub(curr->group);
	free(curr->visible);
	moredirfree(curr);
}

void freestuff(t_opt *flags, h_dir *curr, char **dirs, char *key)
{
	free (flags);
	freedub (dirs);
	freedir (curr);
	free (key);
}

int main(int argc, char const *argv[])
{
	t_opt *flags;
	char **dirs;
	int d_size;
	h_dir *curr;
	char *key;
	int inc;
	int i;

	dirs = NULL;
	curr = malloc(sizeof(h_dir));
	flags = malloc(sizeof(t_opt));
	initflag(flags, &i, &d_size);
	dirs = finishmain(argc, dirs, &d_size, argv);
	flagfix(argc, argv, flags);
	if (d_size == 0)
		dirs = fixdir(dirs, &d_size);
	dirs = checkexist(dirs, d_size, curr, flags);
	key = fixmain(curr, flags);
	mainops(flags, curr, &i, &inc);
	mainprint(flags, key, i, curr);
	endl(flags, d_size, curr);
	dispatchls(flags, dirs, d_size);
	//freestuff(flags, curr, dirs, key);
}
