/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:42:34 by rpassafa          #+#    #+#             */
/*   Updated: 2016/10/01 14:42:35 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strcpy(tmp, src);
	return (tmp);
}
