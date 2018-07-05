/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:31:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/10/28 18:07:05 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	i = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j])
		{
			if (haystack[i + j] == needle[j])
				j++;
			else
				break ;
		}
		if (needle[j] == 0)
			return ((char*)(haystack + i));
		i++;
	}
	return (NULL);
}
