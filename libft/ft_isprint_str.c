/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:29:45 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/05 21:30:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isprint(*str))
			return (0);
	return (1);
}
