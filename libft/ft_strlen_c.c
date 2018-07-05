/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:25:21 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/05 16:42:39 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_c(char const *s, char c)
{
	size_t res;

	res = 0;
	while (*s && *s != c)
	{
		s++;
		res++;
	}
	return (res);
}
