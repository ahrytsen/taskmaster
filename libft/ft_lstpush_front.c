/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 17:20:46 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/05 17:28:37 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpush_front(t_list **l, void const *content, size_t content_size)
{
	t_list *new_lst;

	if (!l)
		return (NULL);
	if (!(new_lst = ft_lstnew(content, content_size)))
		return (NULL);
	ft_lstadd(l, new_lst);
	return (new_lst);
}
