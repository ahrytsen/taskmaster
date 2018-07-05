/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:43:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 19:54:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel_content(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh_lst;
	t_list *buf;
	t_list *tmp;

	fresh_lst = NULL;
	while (lst && f)
	{
		if (!(buf = (*f)(lst)) ||
			!(tmp = ft_lstnew(buf->content, buf->content_size)))
		{
			ft_lstdel(&fresh_lst, ft_lstdel_content);
			return (NULL);
		}
		ft_lstadd_end(&fresh_lst, tmp);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (fresh_lst);
}
