/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagfunextra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 02:14:26 by rpassafa          #+#    #+#             */
/*   Updated: 2016/12/17 02:14:28 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_stradd(char *append, char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_strnew(ft_strlen(append) + ft_strlen(str));
	while (ret[i])
	{
		while (append[j])
		{
			ret[i] = append[j];
			i++;
			j++;
		}
		j = 0;
		while (str[j])
		{
			ret[i] = str[j];
			i++;
			j++;
		}
	}
	return (ret);
}

char	*makespace(int size, int c)
{
	char	*ret;
	int		i;

	if (size < 0)
		return ("");
	i = 0;
	ret = (char*)malloc(size + 1);
	ret[size] = '\0';
	ret = (char*)ft_memset(ret, c, size);
	return (ret);
}

char	*fixneg(char *str)
{
	int		i;
	char	temp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && str[0] != ' ')
		{
			temp = str[0];
			str[0] = '-';
		}
		i++;
	}
	return (str);
}

char	*betterjoin(char *first, char *second)
{
	char *ret;

	ret = ft_strnew(ft_strlen(first) + ft_strlen(second));
	ret = ft_strjoin(first, second);
	return (ret);
}
