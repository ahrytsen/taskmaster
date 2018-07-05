/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:37:57 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 21:45:54 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	long	res;

	res = n;
	i = 1;
	if (res < 0)
	{
		ft_putchar_fd('-', fd);
		res *= -1;
	}
	while (res / i > 9)
		i *= 10;
	while (i > 0)
	{
		ft_putchar_fd(res / i + '0', fd);
		res %= i;
		i /= 10;
	}
}
