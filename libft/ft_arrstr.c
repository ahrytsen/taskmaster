/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:41:47 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/14 21:32:48 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_arrstr(char **arr, char *str)
{
	if (arr && str)
		while (*arr)
		{
			if (ft_strequ(*arr, str))
				return (*arr);
			arr++;
		}
	return (NULL);
}
