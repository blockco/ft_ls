/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:51:57 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:55:15 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putchar(va_list *args, t_flags **flag)
{
	int		c;
	char	*hold;
	t_flags	*tempflag;

	tempflag = *flag;
	c = va_arg(*args, int);
	tempflag->ret = "";
	tempflag->ret = charadder(tempflag->ret, 'a');
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformatingstrings(tempflag->ret, &tempflag);
	hold = ft_strchr(tempflag->ret, 'a');
	hold[0] = c;
	if (c == 0)
	{
		ft_putchar(0);
		tempflag->size = tempflag->size + 1;
	}
}

void	pf_putstr(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (data == NULL)
	{
		tempflag->size = tempflag->size + 6;
		ft_putstr("(null)");
		return ;
	}
	else
		tempflag->ret = ft_strdup((char*)data);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformatingstrings(tempflag->ret, &tempflag);
}

void	pf_putnbr(va_list *args, t_flags **flag)
{
	char	*str;
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	str = NULL;
	data = va_arg(*args, void*);
	isnegative(&tempflag, (long long)data);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_base((int)data, 10);
	else if (tempflag->zflag)
		tempflag->ret = ft_itoa_baseu((ssize_t)data, 10);
	else if (tempflag->j)
		tempflag->ret = ft_itoa_baseu((intmax_t)data, 10);
	else if (tempflag->ll)
		tempflag->ret = ft_itoa_base((long long)data, 10);
	else if (tempflag->l)
		tempflag->ret = ft_itoa_base((long)data, 10);
	else if (tempflag->h)
		tempflag->ret = ft_itoa_base((short)data, 10);
	else if (tempflag->hh)
		tempflag->ret = ft_itoa_base((signed char)data, 10);
	if (!checkoptions(&tempflag) || tempflag->isnegative == 1)
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

void	pf_x_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags	*tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_baseu((unsigned int)data, 16);
	else if (tempflag->zflag)
		tempflag->ret = ft_itoa_baseu((ssize_t)data, 16);
	else if (tempflag->j)
		tempflag->ret = ft_itoa_baseu((uintmax_t)data, 16);
	else if (tempflag->ll)
		tempflag->ret = ft_itoa_baseu((unsigned long long)data, 16);
	else if (tempflag->l)
		tempflag->ret = ft_itoa_baseu((unsigned long)data, 16);
	else if (tempflag->h)
		tempflag->ret = ft_itoa_baseu((unsigned short)data, 16);
	else if (tempflag->hh)
		tempflag->ret = ft_itoa_baseu((unsigned char)data, 16);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

void	pf_xlow_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_baselowu((unsigned int)data, 16);
	else if (tempflag->zflag)
		tempflag->ret = ft_itoa_baselowu((ssize_t)data, 16);
	else if (tempflag->j)
		tempflag->ret = ft_itoa_baselowu((uintmax_t)data, 16);
	else if (tempflag->ll)
		tempflag->ret = ft_itoa_baselowu((unsigned long long)data, 16);
	else if (tempflag->l)
		tempflag->ret = ft_itoa_baselowu((unsigned long)data, 16);
	else if (tempflag->h)
		tempflag->ret = ft_itoa_baselowu((unsigned short)data, 16);
	else if (tempflag->hh)
		tempflag->ret = ft_itoa_baselowu((unsigned char)data, 16);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}
