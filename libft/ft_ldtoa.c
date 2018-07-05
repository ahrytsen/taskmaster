/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 19:22:25 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/29 22:08:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_round(int precision)
{
	double	round;

	round = 0.1;
	while (precision-- > 1)
		round *= 0.1;
	return (round * 0.5);
}

char				*ft_ldtoa(long double nbr, int precision, int dot)
{
	char	*snbr;
	char	*remainder;
	int		i;

	nbr = nbr < 0 ? nbr - ft_round(precision) : nbr + ft_round(precision);
	if (!precision && ((nbr - (long)nbr) >= 0.5 || (nbr - (long)nbr) <= -0.5))
		nbr = nbr < 0 ? nbr - 1.0 : nbr + 1.0;
	snbr = ft_ltoa((long)nbr);
	nbr *= nbr < 0 ? -1 : 1;
	nbr -= (long)nbr;
	i = 1;
	if (precision > 0 || dot)
	{
		remainder = (char*)malloc(sizeof(char) * (precision + 2));
		*remainder = '.';
		remainder[precision + 1] = 0;
		while (precision--)
		{
			remainder[i++] = (long)(nbr * 10) + '0';
			nbr = nbr * 10 - (long)(nbr * 10);
		}
		snbr = ft_strextend(snbr, remainder);
	}
	return (snbr);
}
