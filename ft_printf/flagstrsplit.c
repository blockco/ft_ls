/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagstrsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:45:32 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:45:33 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zerostr(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	char	*buffer;
	int		size;

	tempflag = *flag;
	buffer = "";
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	size = tempflag->zero - ft_strlen(temp);
	if (size < 1)
		return (temp);
	size = ft_strlen(temp) - tempflag->space;
	if (size > 0)
		buffer = makespace('0', size);
	temp = betterjoin(buffer, temp);
	return (temp);
}

char	*signflagstr(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	char	*buffer;
	int		size;

	tempflag = *flag;
	buffer = "";
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	size = tempflag->sign - ft_strlen(temp);
	if (size > 0)
		buffer = makespace(' ', size);
	temp = betterjoin(buffer, temp);
	return (temp);
}

char	*flagformatingstrings(char *str, t_flags **flag)
{
	t_flags	*tempflag;
	char	*temp;

	tempflag = *flag;
	temp = NULL;
	if (((tempflag->precision > 0 || tempflag->precision == -1)
	&& (tempflag->precision - ft_strlen(str) > 0)))
		temp = stringpercision(str, temp, &tempflag);
	if (tempflag->mflag)
		temp = stringmflag(str, temp, &tempflag);
	else if (tempflag->zero > 0)
		temp = zerostr(str, temp, &tempflag);
	if (((tempflag->sign == -1) || (tempflag->sign > 0))
	&& (tempflag->conid > -1))
		temp = signflagstr(str, temp, &tempflag);
	else if (((tempflag->space == -1) || (tempflag->space > 0))
	&& (ft_strcmp(str, "%") != 0))
		temp = strspace(str, temp, &tempflag);
	else if (tempflag->extra > 0)
		temp = extraflag(str, temp, &tempflag);
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	return (temp);
}
