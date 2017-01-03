/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zerohash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:51:26 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:51:27 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zeroflagextra(t_flags *tempflag, int size, char *buffer, char *save)
{
	if (tempflag->precision == 0)
		buffer = makespace(size, '0');
	else if (tempflag->precision > 0)
		buffer = makespace(size, ' ');
	return (betterjoin(buffer, save));
}

char	*zeroflag(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	int		size;
	char	*buffer;
	char	*save;

	buffer = "";
	tempflag = *flag;
	if (tempflag->sign == -1 || tempflag->space == -1)
		tempflag->zero--;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	size = tempflag->zero - ft_strlen(temp);
	if (temp[0] == '-')
		save = ft_strsub(temp, 1, ft_strlen(temp) - 1);
	else
		save = ft_strdup(temp);
	if (size > 0)
	{
		save = zeroflagextra(tempflag, size, buffer, save);
	}
	if (temp[0] == '-')
		temp = betterjoin("-", save);
	else
		temp = ft_strdup(save);
	return (temp);
}

char	*hashflag(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;

	tempflag = *flag;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (ft_strcmp(temp, "0") == 0)
		temp = ft_strdup("0");
	else if (tempflag->conid == 10 && (temp[0] != '0' || temp[1] != 'x'))
		temp = betterjoin("0x", temp);
	else if (tempflag->conid == 11 && (temp[0] != '0' || temp[1] != 'x'))
		temp = betterjoin("0X", temp);
	else if ((tempflag->conid == 7 || tempflag->conid == 6) && temp[0] != '0')
		temp = betterjoin("0", temp);
	return (temp);
}

char	*extraflag(char *str, char *temp, t_flags **flag)
{
	t_flags	*tempflag;
	char	*buffer;

	tempflag = *flag;
	buffer = "";
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (tempflag->extra)
	{
		buffer = makespace(tempflag->extra - ft_strlen(temp), ' ');
		temp = betterjoin(buffer, temp);
	}
	return (temp);
}

char	*spaceflag(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	char	*buffer;

	tempflag = *flag;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	buffer = "";
	if (tempflag->space > 0)
		temp = spaceextra(str, temp, tempflag, NULL);
	else if (tempflag->space == -1 && (tempflag->isnegative == 0) &&
	tempflag->conid != 8 && tempflag->conid != 9 && temp[0] != '-')
	{
		temp = betterjoin(" ", temp);
	}
	else if (tempflag->space == -1)
	{
		if (tempflag->isnegative)
			temp = betterjoin("-", temp);
		else if (tempflag->space == -1 && temp[0] != '-' &&
		tempflag->conid != 8 && tempflag->conid != 9)
			temp = betterjoin(" ", temp);
	}
	temp = betterjoin(buffer, temp);
	return (temp);
}
