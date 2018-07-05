/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:27:26 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/05 21:27:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isascii(*str))
			return (0);
	return (1);
}
