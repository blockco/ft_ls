/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:22:42 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:28:31 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	domore(char *format, t_flags **flag, int *index, va_list *args)
{
	t_flags *tempflag;
	int		findex;

	findex = *index;
	tempflag = *flag;
	tempflag->conid = findfunind(format[findex]);
	if (format[findex] == '%')
	{
		tempflag->ret = percdealer(&tempflag);
		findex++;
	}
	else if (tempflag->conid != -1)
	{
		g_gl[tempflag->conid](args, &tempflag);
		findex++;
	}
	ft_putstr(tempflag->ret);
	tempflag->size = ft_strlen(tempflag->ret) + tempflag->size;
	*index = findex;
}

void	moreish(char *format, t_flags **flag, int *index)
{
	t_flags *tempflag;
	int		findex;
	int		size;

	findex = *index;
	tempflag = *flag;
	tempflag->ret = "";
	tempflag->ret = charadder(tempflag->ret, format[findex]);
	tempflag->ret = (char*)flagformatingstrings(tempflag->ret, &tempflag);
	ft_putstr(tempflag->ret);
	size = ft_strlen(tempflag->ret) + tempflag->size;
	setflags(&tempflag);
	tempflag->size = size;
	findex++;
	*index = findex;
}

void	doelse(char *format, t_flags **flag, int *index)
{
	t_flags *tempflag;
	int		findex;

	findex = *index;
	tempflag = *flag;
	if (!checkoptions(&tempflag) && format[findex] == 'Z')
		moreish((char*)format, &tempflag, &findex);
	else
	{
		tempflag->size = tempflag->size + 1;
		ft_putchar(format[findex]);
		findex++;
	}
	*index = findex;
}

void	finish(char *format, t_flags **flag, int *index, va_list *args)
{
	t_flags *tempflag;
	int		findex;

	findex = *index;
	tempflag = *flag;
	if (format[findex] == '%')
	{
		findex++;
		while (contin((char*)format, findex))
		{
			if (flagcontin((char*)format, findex))
				setsymb(&tempflag, &findex, format);
			else if (format[findex] >= '0' && format[findex] <= '9')
				tempflag->extra = findprecisionextra(format, &findex);
			else if (format[findex] == '.')
				tempflag->precision = findprecision(format, &findex);
			else if (morecontin((char*)format, findex))
				findflags(&tempflag, &findex, format);
		}
		domore((char*)format, &tempflag, &findex, args);
	}
	else
		doelse((char*)format, flag, &findex);
	*index = findex;
}

int		ft_printf(const char *format, ...)
{
	int		findex;
	va_list args;
	t_flags *flag;

	flag = malloc(sizeof(t_flags));
	findex = 0;
	va_start(args, format);
	setflags(&flag);
	while (format[findex])
		finish((char*)format, &flag, &findex, &args);
	va_end(args);
	return (flag->size);
}
