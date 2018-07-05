/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:44:55 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/10/28 13:32:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (i < len)
	{
		if (i < src_len)
			dst[i] = src[i];
		else
			dst[i] = 0;
		i++;
	}
	return (dst);
}
