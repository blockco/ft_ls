/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 05:05:10 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 05:05:25 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exitf(char **str, int i)
{
	ft_putstr("ls: ");
	perror(str[i]);
	exit(EXIT_FAILURE);
}

void	flagfix(int argc, const char **argv, struct s_opt *flags)
{
	if (argc > 1)
		parseinput(argv, flags, argc);
}

void	endl(struct s_opt *flags, int d_size, struct s_dir *curr)
{
	if ((flags->t_op || flags->rec_op) && (d_size > 0 && curr->msize > 1))
		ft_putendl("");
}

int		main(int argc, char const *argv[])
{
	struct s_opt *flags;
	struct s_mor var;
	struct s_dir *curr;

	var.dirs = NULL;
	curr = malloc(sizeof(struct s_dir));
	flags = malloc(sizeof(struct s_opt));
	initflag(flags, &var.i, &var.d_size);
	var.dirs = finishmain(argc, var.dirs, &var.d_size, argv);
	flagfix(argc, argv, flags);
	if (var.d_size == 0)
		var.dirs = fixdir(var.dirs, &var.d_size);
	var.dirs = checkexist(var.dirs, var.d_size, curr, flags);
	var.key = fixmain(curr, flags);
	mainops(flags, curr, &var.i, &var.inc);
	mainprint(flags, var.key, var.i, curr);
	endl(flags, var.d_size, curr);
	dispatchls(flags, var.dirs, var.d_size);
	freestuff(flags, var.dirs, var.key);
}
