/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_extramore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:23:44 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 21:57:06 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*helpit(char *ret, long *in, intmax_t *isize, int base)
{
	intmax_t	size;
	long		n;
	char		*hex;

	hex = ft_strdup("0123456789ABCDEF");
	size = *isize;
	n = *in;
	ret[size] = hex[n % base];
	n = n / base;
	size--;
	*isize = size;
	*in = n;
	return (ret);
}

char	*ft_itoa_base(ssize_t value, int base)
{
	char		*hex;
	intmax_t	n;
	intmax_t	size;
	char		*ret;

	n = (intmax_t)value;
	hex = ft_strdup("0123456789ABCDEF");
	if (n < -9223372036854775807)
		return ("-9223372036854775808");
	if (value == 0)
		return ("0");
	if (value < 0)
		n = (-1 * n);
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

char	*ft_itoa_baselowu(uintmax_t value, uintmax_t base)
{
	char		*hex;
	uintmax_t	n;
	uintmax_t	size;
	char		*ret;

	n = value;
	hex = ft_strdup("0123456789abcdef");
	if (value == 0)
		return ("0");
	size = findsize(n, base);
	ret = (char*)malloc(size + 1);
	ret[size] = '\0';
	size--;
	while (n)
	{
		ret[size] = hex[n % base];
		n = n / base;
		size--;
	}
	return (ret);
}

char	*ft_itoa_baseu(uintmax_t value, uintmax_t base)
{
	char		*hex;
	uintmax_t	n;
	uintmax_t	size;
	char		*ret;

	n = value;
	hex = ft_strdup("0123456789ABCDEF");
	if (value == 0)
		return ("0");
	size = findsize(n, base);
	ret = (char*)malloc(size + 1);
	ret[size] = '\0';
	size--;
	while (n)
	{
		ret[size] = hex[n % base];
		n = n / base;
		size--;
	}
	return (ret);
}

int		findsize(uintmax_t value, int base)
{
	uintmax_t size;

	size = 0;
	while (value)
	{
		size++;
		value = value / base;
	}
	return (size);
}
