/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagformating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:44:32 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:44:33 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*percisionflag(char *str, char *temp, t_flags **flag)
{
	int		size;
	char	*test;
	t_flags *tempflag;

	tempflag = *flag;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (tempflag->precision == -1)
		return (temp);
	if (tempflag->precision == -1 && ft_strcmp("0", temp) == 0)
		return ("");
	size = ft_strlen(temp);
	if (temp[0] == '-')
	{
		test = ft_strsub((char const*)temp, 1, ft_strlen(temp) - 1);
		size--;
	}
	else
		test = ft_strsub((char const*)temp, 0, ft_strlen(temp));
	temp = makespace((tempflag->precision - size), '0');
	temp = betterjoin(temp, test);
	if (str[0] == '-')
		temp = betterjoin("-", temp);
	return (temp);
}

char	*mflag(char *str, char *temp, t_flags **flag)
{
	t_flags	*tempflag;
	int		size;
	char	*buffer;

	tempflag = *flag;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	size = tempflag->mflag - ft_strlen(temp);
	if (size > 0)
	{
		buffer = makespace(size, ' ');
		temp = betterjoin(temp, buffer);
	}
	return (temp);
}

char	*extendflagformat(t_flags *tempflag, char *temp, char *str)
{
	if ((tempflag->precision > 0 || tempflag->precision == -1))
		temp = percisionflag(str, temp, &tempflag);
	if ((tempflag->mflag == -1) || tempflag->mflag > tempflag->precision)
		temp = mflag(str, temp, &tempflag);
	else if (tempflag->zero)
		temp = zeroflag(str, temp, &tempflag);
	if (tempflag->hash == -1 && (tempflag->conid == 6 || tempflag->conid == 7
	|| tempflag->conid == 11 || tempflag->conid == 10))
		temp = hashflag(str, temp, &tempflag);
	if (((tempflag->sign == -1) || (tempflag->sign > 0))
	&& (tempflag->conid > -1))
		temp = signflag(str, temp, &tempflag);
	else if (((tempflag->space == -1) || (tempflag->space > 0))
	&& (ft_strcmp(str, "%") != 0))
		temp = spaceflag(str, temp, &tempflag);
	else if (tempflag->extra > 0)
		temp = extraflag(str, temp, &tempflag);
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	return (temp);
}

char	*flagformating(char *str, t_flags **flag)
{
	t_flags *tempflag;
	char	*temp;

	tempflag = *flag;
	temp = NULL;
	if (tempflag->isnegative == 1 && tempflag->ret[0] != '-')
		temp = betterjoin("-", tempflag->ret);
	if (ft_atoi(str) == 0 && tempflag->precision == -1)
	{
		tempflag->precision = -2;
		temp = "";
	}
	if (tempflag->hash == -1 && (tempflag->zero > 0 || tempflag->mflag > 0))
	{
		if (tempflag->zero > 1)
			tempflag->zero = tempflag->zero - 2;
		else if (tempflag->zero == 1)
			tempflag->zero = 0;
		if (tempflag->mflag > 0)
			tempflag->mflag = tempflag->mflag - 2;
	}
	temp = extendflagformat(tempflag, temp, str);
	return (temp);
}
