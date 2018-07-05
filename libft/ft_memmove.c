/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:58:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 18:29:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long				i;
	unsigned char		*dest;
	const unsigned char	*sorc;

	i = len;
	dest = (unsigned char*)dst;
	sorc = (unsigned char*)src;
	if (dest > sorc)
		while (i--)
			dest[i] = sorc[i];
	else if (dest < sorc)
		while (i--)
			*dest++ = *sorc++;
	return (dst);
}
