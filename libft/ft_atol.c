/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:07:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:10:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-' ? -1 : 1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		i += (res ? 1 : 0);
		if (i > 19 || res < 0 || (i && !res))
			return (sign == 1 ? -1 : 0);
	}
	return (sign * res);
}
