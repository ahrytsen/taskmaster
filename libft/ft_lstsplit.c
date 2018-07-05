/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:33:33 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/10 12:51:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel_content(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

t_list		*ft_lstsplit(char const *s, char c)
{
	size_t	wlen;
	t_list	*split_lst;

	wlen = 0;
	split_lst = NULL;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			wlen = ft_strlen_c(s, c);
			if (!(ft_lstpush_back(&split_lst, ft_strsub(s, 0, wlen), wlen + 1)))
			{
				ft_lstdel(&split_lst, ft_lstdel_content);
				return (NULL);
			}
			s += wlen;
		}
		else
			s++;
	}
	return (split_lst);
}
