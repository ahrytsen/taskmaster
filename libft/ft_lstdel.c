/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:05:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/04 19:04:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *buf;

	if (alst)
		while (*alst)
		{
			buf = (*alst)->next;
			del ? del((*alst)->content, (*alst)->content_size) : 0;
			free(*alst);
			*alst = buf;
		}
}
