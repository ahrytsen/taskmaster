/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 13:52:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/10/28 14:33:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t s1_i;
	size_t s2_i;

	s1_i = ft_strlen(s1);
	s2_i = 0;
	while (s2[s2_i] && s2_i < n)
		s1[s1_i++] = s2[s2_i++];
	s1[s1_i] = 0;
	return (s1);
}
