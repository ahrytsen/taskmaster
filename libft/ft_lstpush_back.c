/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:44:01 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/18 09:29:14 by yvyliehz         ###   ########.fr       */
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
