#include "ft_ls.h"

char	*getyear(char *str)
{
	int		i;
	char	*ret;
	int		a;

	ret = ft_strnew(4);
	i = ft_strlen(str) - 5;
	a = 0;
	while (str[i])
	{
		ret[a] = str[i];
		a++;
		i++;
	}
	return (ret);
}

void	morelink(struct stat sb_l, struct s_dir *curr, int i)
{
	static time_t	now;

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

void	evenmorelnk(struct stat sb_l, struct s_dir *curr, int i)
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

int		getlnk(struct stat sb_l, struct s_dir **current, int i)
{
	struct passwd	*pwuser;
	struct group	*grpnam;
	struct s_dir			*curr;

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

void	initial(struct s_dir **current, char **str)
{
	int			temp;
	int 		i;
	struct stat	sb_l;
	struct s_dir		*curr;
	long long	block;

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
