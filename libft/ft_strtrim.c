/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:04:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 15:42:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	st;
	size_t	len;
	char	*new_string;

	st = 0;
	new_string = NULL;
	if (!s)
		return (NULL);
	while ((s[st] == ' ' || s[st] == '\n' || s[st] == '\t') && s[st])
		s++;
	len = ft_strlen(s);
	while ((s[len - 1] == ' ' || s[len - 1] == '\n' ||
			s[len - 1] == '\t') && len > 0)
		len--;
	new_string = ft_strsub(s, 0, len);
	return (new_string);
}
