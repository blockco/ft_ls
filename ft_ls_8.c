/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:56:57 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:56:58 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*normkey(struct s_dir *curr)
{
	char	*ret;

	ret = betterjoin("%-", ft_itoa_base((curr->longest + 1), 10));
	ret = betterjoin(ret, "s");
	return (ret);
}

void	makevisible(struct s_dir *curr)
{
	int	i;

	i = 0;
	while (i < curr->msize)
	{
		curr->visible[i] = 1;
		i++;
	}
}

void	handle_op(struct s_dir *curr, struct s_opt *flags)
{
	if (flags->a_op)
		makevisible(curr);
}

void	revprint(struct s_dir *curr)
{
	int	temp;

	temp = curr->msize;
	temp--;
	while (temp > -1)
	{
		if (curr->visible[curr->print[temp]])
			ft_printf("%s\n", curr->list[curr->print[temp]]);
		temp--;
	}
}

void	normprint(struct s_dir *curr)
{
	int i;

	i = 0;
	while (i < curr->msize)
	{
		if (curr->visible[curr->print[i]])
			ft_printf("%s\n", curr->list[curr->print[i]]);
		i++;
	}
}
