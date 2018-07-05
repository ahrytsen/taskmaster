/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:07:09 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/02 20:08:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_arr(char **src_arr)
{
	char	**new_arr;
	size_t	arr_l;

	arr_l = 0;
	while (src_arr[arr_l])
		arr_l++;
	if (!(new_arr = ft_memalloc(sizeof(char*) * (arr_l + 1))))
		return (NULL);
	arr_l = 0;
	while (src_arr[arr_l])
	{
		new_arr[arr_l] = ft_strdup(src_arr[arr_l]);
		arr_l++;
	}
	return (new_arr);
}
