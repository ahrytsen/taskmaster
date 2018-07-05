/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:33:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/12 15:37:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_range(char c, int base)
{
	if ((base <= 10 && c >= '0' && c < base + '0')
		|| (base > 10 && ((c >= 'a' && c < 'a' + base - 10)
							|| (c >= 'A' && c < 'A' + base - 10))))
		return (1);
	else
		return (0);
}

static int	to_digit(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (10 + c - 'a');
	else
		return (10 + c - 'A');
}

long		ft_atol_base(const char *str, int base)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (base == 10 && (*str == '-' || *str == '+'))
		sign = (*str++ == '-' ? -1 : 1);
	while (in_range(*str, base))
	{
		res = res * base + to_digit(*str++);
		i += (res ? 1 : 0);
		if (i > 19 || res < 0 || (i && !res))
			return (sign == 1 ? -1 : 0);
	}
	return (sign * res);
}
