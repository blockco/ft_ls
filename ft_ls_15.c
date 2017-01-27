/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_15.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:57:42 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:57:43 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**checkexist(char **dirs, int d_size, struct s_dir *c, struct s_opt *f)
{
	struct s_emor var;

	setthem(&var.a, &var.i, &var.b, &var.found);
	var.ret = (char**)malloc(sizeof(char*) * d_size + 1);
	lastexist(c, d_size, var.ret);
	while (var.i < d_size)
	{
		if (NULL == (var.dir = opendir(dirs[var.i])))
		{
			if (errno == 20 || (errno == 2 && !f->rec_op))
				c->list[var.b++] = ft_strdup(dirs[var.i]);
			else if (errno > 0)
				var.found = founddir(dirs, var.found, var.i);
		}
		else
			var.ret[var.a++] = ft_strdup(dirs[var.i]);
		var.i = seti(var.i, dirs, var.dir);
	}
	makenull(var.a, var.b, var.ret, c->list);
	return (var.ret);
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
