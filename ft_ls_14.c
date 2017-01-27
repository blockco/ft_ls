/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 04:57:33 by rpassafa          #+#    #+#             */
/*   Updated: 2017/01/27 04:57:35 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	intitthem(int *opend, int *i, int *count)
{
	*opend = 0;
	*i = 1;
	*count = 0;
}

int		easyc(int *opend, int i)
{
	*opend = 1;
	i++;
	return (i);
}

char	**storedirs(const char **argv, int *count, int argc)
{
	int		i;
	char	**ret;
	int		opend;

	intitthem(&opend, &i, count);
	while (argc > i)
		i = retit(argv, i, count);
	ret = (char**)malloc(sizeof(char*) * (*count + 1));
	*count = 0;
	i = 1;
	while (argc > i)
	{
		if (ft_strcmp("--", argv[i]) == 0 && !opend)
			i = easyc(&opend, i);
		if (!argv[i])
			break ;
		if ((argv[i][0] != '-') || opend || (argv[i][0] == '-' && !argv[i][1]))
		{
			*count = shelp(argv, *count, ret, i);
			opend = 1;
		}
		i++;
	}
	ret[*count] = NULL;
	return (ret);
}

int		founddir(char **dirs, int found, int i)
{
	ft_putstr("ls: ");
	perror(dirs[i]);
	found = 1;
	return (found);
}

void	setthem(int *a, int *i, int *b, int *found)
{
	*a = 0;
	*i = 0;
	*b = 0;
	*found = 0;
}
