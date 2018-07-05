/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:22:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/03 21:36:03 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
	{
		((unsigned char*)dst)[i] = (unsigned char)((unsigned char*)src)[i];
		if ((unsigned char)((unsigned char*)src)[i] == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
