/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_funmore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:24:11 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 22:18:17 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_oup_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_baselowu((unsigned long int)data, 8);
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
		tempflag->ret = ft_itoa_baselowu((unsigned short)data, 8);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

void	pf_p_handle(va_list *args, t_flags **flag)
{
	void	*ptr;
	char	*str;
	t_flags *tempflag;

	tempflag = *flag;
	ptr = va_arg(*args, void*);
	str = ft_itoa_baselowu((uintmax_t)ptr, 16);
	tempflag->ret = ft_strjoin("0x", str);
}

void	pf_u_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	if (checkzeroflag(&tempflag) == 1)
		tempflag->ret = ft_itoa_baselowu((unsigned int)data, 10);
	else if (tempflag->zflag)
		tempflag->ret = ft_itoa_baselowu((size_t)data, 10);
	else if (tempflag->j)
		tempflag->ret = ft_itoa_baselowu((uintmax_t)data, 10);
	else if (tempflag->ll)
		tempflag->ret = ft_itoa_baselowu((unsigned long long)data, 10);
	else if (tempflag->l)
		tempflag->ret = ft_itoa_baselowu((unsigned long)data, 10);
	else if (tempflag->h)
		tempflag->ret = ft_itoa_baselowu((unsigned short)data, 10);
	else if (tempflag->hh)
		tempflag->ret = ft_itoa_baselowu((unsigned char)data, 10);
	tempflag->sign = 0;
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

void	pf_uup_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	tempflag->ret = ft_itoa_baselowu((unsigned long)data, 10);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}

void	pf_dup_handle(va_list *args, t_flags **flag)
{
	void	*data;
	t_flags *tempflag;

	tempflag = *flag;
	data = va_arg(*args, void*);
	tempflag->ret = ft_itoa_baselowu((long)data, 10);
	if (!checkoptions(&tempflag))
		tempflag->ret = (char*)flagformating(tempflag->ret, &tempflag);
}
