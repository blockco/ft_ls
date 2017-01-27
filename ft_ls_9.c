/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:57:03 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:57:04 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*quickdirchange(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	return (ret);
}

void	morenorm(struct s_dir *curr, char *str, struct s_opt *flags)
{
	initstruct(curr, str, 0);
	findmax(curr);
	if (flags->t_op)
		lex_sort(&curr, time_sort);
	else
		lex_sort(&curr, name_sort);
	handle_op(curr, flags);
}

int		morestuff(int first, char *str, struct s_opt *flags, struct s_dir *curr)
{
	if (first++)
		ft_printf("%s:\n", str);
	if (flags->rev_op)
		revprint(curr);
	else
		normprint(curr);
	return (first);
}

int		checkifnorm(struct s_dir *curr, int i)
{
	if (curr->list[curr->print[i]] && curr->visible[curr->print[i]]
		&& curr->isdir[curr->print[i]]
		&& checkinf(curr->list[curr->print[i]]) &&
		!curr->islnk[curr->print[i]])
		return (1);
	return (0);
}

void	dosome(int first)
{
	if (first > 0)
		ft_printf("\n");
}
