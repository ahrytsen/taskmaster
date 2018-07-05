/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 06:12:44 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/10/28 06:43:50 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*fresh_memory;

	if (!(fresh_memory = malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		((unsigned char*)fresh_memory)[i++] = 0;
	return (fresh_memory);
}
