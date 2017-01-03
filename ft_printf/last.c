/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:52:48 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:06:25 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_o_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_baselowu((unsigned int)data, 8);
	else if (tempflag->zflag)
		tempflag->ret = ft_itoa_baselowu((ssize_t)data, 8);
	else if (tempflag->j)
		tempflag->ret = ft_itoa_baselowu((uintmax_t)data, 8);
	else if (tempflag->ll)
		tempflag->ret = ft_itoa_baselowu((unsigned long long)data, 8);
	else if (tempflag->l)
		tempflag->ret = ft_itoa_baselowu((unsigned long)data, 8);
	else if (tempflag->h)
		tempflag->ret = ft_itoa_baselowu((unsigned short)data, 8);
	else if (tempflag->hh)
		tempflag->ret = ft_itoa_baselowu((unsigned char)data, 8);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

char	*ft_itoa_baseint(long value, int base)
{
	char		*hex;
	long		n;
	intmax_t	size;
	char		*ret;

	n = value;
	hex = ft_strdup("0123456789ABCDEF");
	if (value == 0)
		return ("0");
	if (value < 0)
		n = -1 * n;
	size = findsize(n, base);
	if (value < 0 && base == 10)
		size++;
	ret = (char*)malloc(size + 1);
	ret[size] = '\0';
	size--;
	while (n)
		ret = helpit(ret, &n, &size, base);
	if (value < 0 && base == 10)
		ret[0] = '-';
	return (ret);
}
