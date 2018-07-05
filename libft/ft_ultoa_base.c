/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:56:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/19 13:43:37 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(size_t value, int base)
{
	int	res;

	res = 2;
	while (value >= (size_t)base)
	{
		value /= base;
		res++;
	}
	return (res);
}

char		*ft_ultoa_base(size_t value, int base, char st_l)
{
	int		size;
	char	*res;

	size = ft_getsize(value, base);
	if (!(res = (char*)malloc(sizeof(char) * size--)))
		return (NULL);
	res[size--] = 0;
	while (value >= (size_t)base)
	{
		res[size] = (value % base >= 10) ? value % base + st_l - 10 :
			value % base + '0';
		value /= base;
		size--;
	}
	res[size] = (value % base >= 10) ? value % base + st_l - 10 :
		value % base + '0';
	return (res);
}
