/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:37:31 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/05 15:21:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dstlen;
	size_t		addlen;
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	addlen = dstsize;
	while (addlen-- && *dst)
		dst++;
	dstlen = dst - d;
	addlen = dstsize - dstlen;
	if (!addlen)
		return (dstlen + ft_strlen(src));
	while (*src)
	{
		if (addlen != 1)
		{
			*dst++ = *src;
			addlen--;
		}
		src++;
	}
	*dst = 0;
	return (dstlen + (src - s));
}
