/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:44:01 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/16 18:15:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpush_back(t_list **lst, void const *content, size_t content_size)
{
	t_list *new_lst;

	if (!lst)
		return (NULL);
	if (!(new_lst = ft_lstnew(content, content_size)))
		return (NULL);
	ft_lstadd_end(lst, new_lst);
	return (new_lst);
}
