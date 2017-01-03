/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signflag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:44:44 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:02:04 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		checkzeroif(t_flags *tempflag, int size, char **buffer)
{
	*buffer = ft_strdup("");
	if ((tempflag->sign - size) > 0 && (tempflag->zero == 0
	|| (tempflag->precision > 0 || tempflag->precision == -1)))
		return (1);
	return (0);
}

int		checkzeroifone(t_flags *tempflag, char *str, int zero)
{
	if (str[0] == '-' && zero == 0
	&& tempflag->conid != 6 && tempflag->conid != 7
	&& tempflag->conid != 0 && tempflag->conid != 1)
		return (1);
	return (0);
}

char	*signflagextend(char *temp, t_flags *tempflag, int zero, char *str)
{
	char	*buffer;
	int		size;

	size = ft_strlen(temp);
	if (str[0] == '-')
		temp = ft_strsub((char const*)temp, 1, ft_strlen(temp));
	else
	{
		temp = ft_strsub((char const*)temp, 0, ft_strlen(temp));
		size++;
	}
	if (checkzeroif(tempflag, size, &buffer))
		buffer = makespace((tempflag->sign - size), ' ');
	else if (tempflag->zero == -1)
	{
		buffer = makespace((tempflag->sign - size), '0');
		temp = betterjoin(buffer, temp);
		buffer = "";
	}
	if (checkzeroifone(tempflag, str, zero))
		temp = betterjoin("-", temp);
	else if (zero == 0)
		temp = betterjoin("+", temp);
	return (betterjoin(buffer, temp));
}

char	*signflag(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	int		size;
	int		zero;

	tempflag = *flag;
	zero = 0;
	size = 0;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (ft_strcmp(temp, "0") == 0)
		zero = 1;
	if (tempflag->sign > 0)
		temp = signflagextend(temp, tempflag, zero, str);
	else if (tempflag->sign == -1 && zero == 0
	&& tempflag->conid != 6 && tempflag->conid != 7
	&& tempflag->conid != 0 && tempflag->conid != 1)
	{
		if (str[0] == '-' && temp[0] != '-')
			temp = betterjoin("-", temp);
		else if (str[0] != '-')
			temp = betterjoin("+", temp);
	}
	return (temp);
}

char	*spaceextra(char *str, char *temp, t_flags *tempflag, char *t)
{
	int		size;
	char	*buffer;

	t = NULL;
	size = 0;
	size = ft_strlen(temp);
	if (str[0] == '-')
		t = ft_strsub((char const*)temp, 1, ft_strlen(temp) - 1);
	else
		t = ft_strsub((char const*)str, 0, ft_strlen(temp));
	size++;
	if ((tempflag->space - size) > 0)
	{
		buffer = makespace((tempflag->space - size), ' ');
		if (str[0] == '-')
			temp = betterjoin("-", temp);
		else
			temp = betterjoin(" ", temp);
		temp = betterjoin(buffer, temp);
		return (temp);
	}
	return (t);
}
