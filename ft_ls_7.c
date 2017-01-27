/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:56:52 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:56:53 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	noz(char c)
{
	char	*str;

	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	ft_printf("ls: illegal option -- %c\n", c);
	ft_putendl("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]");
	exit(1);
}

void	checkflag(char c, struct s_opt *flags)
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

void	printflags(struct s_opt *flags)
{
	ft_printf("%d\n%d\n%d\n%d\n%d\n%d\n", flags->l_op, flags->reg_ls,
	flags->rec_op, flags->a_op, flags->rev_op,
	flags->t_op);
}

int		moreparse(int i, int c, const char **input, struct s_opt *flags)
{
	while (input[i][c])
	{
		if (input[i][c] == '-')
			c++;
		checkflag(input[i][c++], flags);
	}
	return (c);
}

char	*parseinput(const char **input, struct s_opt *flags, int argc)
{
	int		i;
	int		c;
	char	*str;

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
			break ;
		if (input[i][c] == '-' && (input[i][c + 1]))
			c = moreparse(i, c, input, flags);
		i++;
	}
	return (str);
}
