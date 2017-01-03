/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagformatingstrings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 02:09:06 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 02:09:08 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*stringpercision(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;

	tempflag = *flag;
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (tempflag->precision == -1 && (tempflag->conid == 0
	|| tempflag->conid == 1))
		return ("");
	if ((size_t)tempflag->precision < ft_strlen(temp))
		temp = ft_strsub(temp, 0, tempflag->precision);
	return (temp);
}

char	*stringmflag(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	char	*buffer;
	int		change;

	tempflag = *flag;
	buffer = "";
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	change = tempflag->mflag - ft_strlen(temp);
	if (tempflag->mflag > 0)
		buffer = makespace(change, ' ');
	temp = betterjoin(temp, buffer);
	return (temp);
}

char	*strspace(char *str, char *temp, t_flags **flag)
{
	t_flags *tempflag;
	char	*buffer;
	int		size;

	tempflag = *flag;
	buffer = "";
	if (temp == NULL)
		temp = ft_strdup((const char*)str);
	if (tempflag->space == -1)
		tempflag->space = 1;
	size = ft_strlen(temp) - tempflag->space;
	if (size > 0)
		buffer = makespace(' ', size);
	temp = betterjoin(buffer, temp);
	return (temp);
}
