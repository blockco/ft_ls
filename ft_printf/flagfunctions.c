/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 02:11:18 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 02:11:21 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	isnegative(t_flags **flag, intmax_t data)
{
	t_flags *tempflag;

	tempflag = *flag;
	if (data < 0)
		tempflag->isnegative = (1);
	else
		tempflag->isnegative = (0);
	*flag = tempflag;
}

int		checkzeroflag(t_flags **flag)
{
	t_flags *tempflag;

	tempflag = *flag;
	if (tempflag->zflag == 0 && tempflag->j == 0 &&
		tempflag->ll == 0 && tempflag->l == 0 && tempflag->h == 0
		&& tempflag->hh == 0)
		return (1);
	return (0);
}

int		checkoptions(t_flags **flag)
{
	t_flags *tempflag;

	tempflag = *flag;
	if (tempflag->space == 0 && tempflag->sign == 0 &&
		tempflag->hash == 0 && tempflag->zero == 0 && tempflag->mflag == 0 &&
		tempflag->extra == 0 && tempflag->precision == 0)
		return (1);
	return (0);
}
