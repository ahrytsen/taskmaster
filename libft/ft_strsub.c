/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:37:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 14:34:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_string;

	i = 0;
	if (!s || !(new_string = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[start + i];
		i++;
	}
	return (new_string);
}
