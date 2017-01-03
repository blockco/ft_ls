/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:43:48 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:43:50 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	setflags(t_flags **flag)
{
	t_flags *tempflag;

	tempflag = *flag;
	tempflag->hh = 0;
	tempflag->h = 0;
	tempflag->l = 0;
	tempflag->ll = 0;
	tempflag->j = 0;
	tempflag->hash = 0;
	tempflag->zflag = 0;
	tempflag->mflag = 0;
	tempflag->sign = 0;
	tempflag->space = 0;
	tempflag->precision = 0;
	tempflag->isnegative = 0;
	tempflag->zero = 0;
	tempflag->conid = 0;
	tempflag->size = 0;
	tempflag->extra = 0;
	tempflag->ret = "";
}

int		findprecision(const char *format, int *findex)
{
	int i;
	int temp;

	i = 0;
	temp = *findex;
	temp++;
	while (format[temp] >= '1' && format[temp] <= '9')
	{
		if (format[temp + 1] >= '0' && format[temp + 1] <= '9')
		{
			i = i + format[temp] - 48;
			i = i * 10;
		}
		else
			i = i + format[temp] - 48;
		temp++;
	}
	*findex = temp;
	if (i == 0)
		i = -1;
	return (i);
}

int		findhash(const char *format, int *findex)
{
	int temp;

	format = NULL;
	temp = *findex;
	temp++;
	*findex = temp;
	return (-1);
}

int		findprecisionspace(const char *format, int *findex)
{
	int i;
	int temp;

	i = 0;
	temp = *findex;
	temp++;
	while (format[temp] >= '1' && format[temp] <= '9')
	{
		if (format[temp + 1] >= '0' && format[temp + 1] <= '9')
		{
			i = i + format[temp] - 48;
			i = i * 10;
		}
		else
			i = i + format[temp] - 48;
		temp++;
	}
	*findex = temp;
	if (i == 0)
		i = -1;
	return (i);
}
