/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:22:05 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/05 21:23:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isalpha(*str))
			return (0);
	return (1);
}
