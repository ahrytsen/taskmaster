/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:31:46 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/02 20:36:14 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlst;

	if (!(newlst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	newlst->content = NULL;
	newlst->content_size = 0;
	newlst->next = NULL;
	if (!content || !content_size)
		return (newlst);
	else if ((newlst->content = (void*)malloc(content_size)))
	{
		ft_memcpy(newlst->content, content, content_size);
		newlst->content_size = content_size;
	}
	else
	{
		free(newlst);
		return (NULL);
	}
	return (newlst);
}
