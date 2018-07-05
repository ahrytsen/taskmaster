/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:04:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 21:45:57 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long	i;
	long	res;

	res = n;
	i = 1;
	if (res < 0)
	{
		ft_putchar('-');
		res *= -1;
	}
	while (res / i > 9)
		i *= 10;
	while (i > 0)
	{
		ft_putchar(res / i + '0');
		res %= i;
		i /= 10;
	}
}
