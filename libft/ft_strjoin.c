/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:47:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/07 20:30:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	size_t	len;
	char	*new_string;

	if (!s1 && !s2)
		return (NULL);
	j = 0;
	len = (s1 ? ft_strlen(s1) : 0UL) + (s2 ? ft_strlen(s2) : 0UL);
	if (!(new_string = ft_strnew(len)))
		return (NULL);
	while (s1 && *s1 && j < len)
		new_string[j++] = *s1++;
	while (s2 && *s2 && j < len)
		new_string[j++] = *s2++;
	return (new_string);
}
