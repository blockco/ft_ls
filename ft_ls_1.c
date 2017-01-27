/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:55:47 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:56:21 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	freedub(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	moredirfree(struct s_dir *curr)
{
	free(curr->isblock);
	free(curr->block_dev);
	free(curr->block_min);
	free(curr->print);
	free(curr->islnk);
}

void	freedir(struct s_dir *curr)
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

void	freestuff(struct s_opt *flags, char **dirs, char *key)
{
	free(flags);
	freedub(dirs);
	free(key);
}

void	freestuffagain(struct s_opt *flags, char *key)
{
	free(flags);
	free(key);
}
