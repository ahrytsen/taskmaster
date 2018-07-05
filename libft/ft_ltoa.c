/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 13:57:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/19 14:25:02 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long value)
{
	long	val;
	int		size;
	char	*res;

	val = value;
	size = value < 0 ? 3 : 2;
	while ((val > 9 || val < -9) && (val /= 10))
		size++;
	if (!(res = (char*)malloc(sizeof(char) * size--)))
		return (NULL);
	res[size--] = '\0';
	(value < 0) ? res[0] = '-' : 0;
	while (value > 9 || value < -9)
	{
		res[size--] = value % 10 * (value < 0 ? -1 : 1) + '0';
		value /= 10;
	}
	res[size] = value % 10 * (value < 0 ? -1 : 1) + '0';
	return (res);
}
