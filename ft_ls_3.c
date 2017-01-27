/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:56:30 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:56:31 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	mallocstruct(struct s_dir **current)
{
	struct s_dir	*curr;

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

char	*intit_perm(int isdir, int islnk)
{
	if (isdir)
		return (ft_strdup("d"));
	else if (islnk)
		return (ft_strdup("l"));
	return (ft_strdup("-"));
}

char	*findperm(char c)
{
	if (c == '7')
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

char	*permstr(char *perm, int isdir, int isdev, int islnk)
{
	int		i;
	char	*ret;

	if (isdir)
		i = 2;
	else
		i = 3;
	ret = intit_perm(isdir, islnk);
	while (perm[i])
	{
		ret = betterjoin(ret, findperm(perm[i]));
		i++;
	}
	if (isdev)
		ret = betterjoin("crw", ret);
	return (ret);
}

char	*makepath(char *curdir, char *file)
{
	char	*temp;

	temp = betterjoin(curdir, "/");
	return (betterjoin(temp, file));
}
