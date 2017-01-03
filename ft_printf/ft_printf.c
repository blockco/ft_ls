/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:50:48 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:20:45 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char *g_format = "sSpdDioOuUxXcC";

void	(*g_gl[14])(va_list *ptr, t_flags **flag) =
{
	&pf_putstr,
	&pf_putstr,
	&pf_p_handle,
	&pf_putnbr,
	&pf_dup_handle,
	&pf_putnbr,
	&pf_o_handle,
	&pf_oup_handle,
	&pf_u_handle,
	&pf_uup_handle,
	&pf_xlow_handle,
	&pf_x_handle,
	&pf_putchar,
	&pf_putchar,
};

int		findfunind(char c)
{
	int i;

	i = 0;
	while (g_format[i])
	{
		if (g_format[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		contin(char *format, int findex)
{
	if (format[findex] == '#' || format[findex] == '0'
		|| format[findex] == '-' || format[findex] == '+' ||
		format[findex] == ' ' ||
		(format[findex] >= '0' && format[findex] <= '9') ||
		format[findex] == '.' ||
		(format[findex] == 'l' && format[findex + 1] == 'l') ||
		(format[findex] == 'h' && format[findex + 1] == 'h') ||
		format[findex] == 'h' || format[findex] == 'l' ||
		format[findex] == 'j' || format[findex] == 'z')
		return (1);
	else
		return (0);
}

int		flagcontin(char *format, int findex)
{
	if (format[findex] == '#' || format[findex] == '0'
	|| format[findex] == '-' || format[findex] == '+' ||
	format[findex] == ' ')
		return (1);
	else
		return (0);
}

int		morecontin(char *format, int findex)
{
	if ((format[findex] == 'l' && format[findex + 1] == 'l') ||
	(format[findex] == 'h' && format[findex + 1] == 'h') ||
	format[findex] == 'h' || format[findex] == 'l' ||
	format[findex] == 'j' || format[findex] == 'z')
		return (1);
	else
		return (0);
}

char	*charadder(char *str, char c)
{
	char *temp;

	temp = (char*)malloc(2);
	temp[0] = c;
	temp[1] = '\0';
	return (betterjoin(str, temp));
}
