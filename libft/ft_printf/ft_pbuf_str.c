/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbuf_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 19:54:13 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 22:25:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_buflen(t_buf *pbuf_head)
{
	size_t	size;

	size = 0;
	while (pbuf_head)
	{
		size += pbuf_head->len;
		pbuf_head = pbuf_head->next;
	}
	return (size);
}

ssize_t			ft_buftostr(char **line, t_buf *pbuf, t_buf *pbuf_head)
{
	ssize_t	size;
	ssize_t	tmp_sz;
	t_buf	*tmp;

	size = (!pbuf || !line) ? -1 : ft_buflen(pbuf_head);
	line ? (*line = NULL) : 0;
	tmp_sz = 0;
	if (size > 0 && !(*line = ft_memalloc(sizeof(char) * (size + 1))))
		size = -1;
	while (pbuf_head)
	{
		tmp = pbuf_head->next;
		if (size > 0)
			ft_memcpy(*line + tmp_sz, pbuf_head->str, pbuf_head->len);
		free(pbuf_head->str);
		tmp_sz += pbuf_head->len;
		free(pbuf_head);
		pbuf_head = tmp;
	}
	return (size);
}
