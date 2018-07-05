/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:18:01 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/19 17:02:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_buf(int fd, t_buf *pbuf, t_buf *pbuf_head)
{
	ssize_t	ret;
	t_buf	*tmp;

	ret = 0;
	while (pbuf_head)
	{
		tmp = pbuf_head->next;
		pbuf || fd >= 0 ? write(fd, pbuf_head->str, pbuf_head->len) : 0;
		free(pbuf_head->str);
		ret += pbuf_head->len;
		free(pbuf_head);
		pbuf_head = tmp;
	}
	return (pbuf || fd >= 0 ? ret : -1);
}

void	ft_putchar_buf(t_buf **pbuf, int c)
{
	char	buf[5];
	int		len;

	if ((MB_CUR_MAX == 1 || c <= 0x7F) && (len = 1))
		buf[0] = c;
	else if (c <= 0x7FF && (len = 2))
	{
		buf[0] = (c >> 6) + 0xC0;
		buf[1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF && (len = 3))
	{
		buf[0] = (c >> 12) + 0xE0;
		buf[1] = ((c >> 6) & 0x3F) + 0x80;
		buf[2] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF && (len = 4))
	{
		buf[0] = (c >> 18) + 0xF0;
		buf[1] = ((c >> 12) & 0x3F) + 0x80;
		buf[2] = ((c >> 6) & 0x3F) + 0x80;
		buf[3] = (c & 0x3F) + 0x80;
	}
	ft_putstr_buf(pbuf, buf, len);
}

void	ft_putstr_buf(t_buf **pbuf, char *str, ssize_t len)
{
	while (len && *pbuf)
	{
		if ((*pbuf)->len == PBS)
		{
			(*pbuf)->next = ft_newbuf();
			(*pbuf)->next->id = (*pbuf)->id + 1;
			*pbuf = (*pbuf)->next;
		}
		(*pbuf)->str[(*pbuf)->len++] = *str++;
		len--;
	}
}

void	ft_putustr_buf(t_buf **pbuf, int *str, ssize_t len)
{
	while ((len -= ft_wcharlen(*str)) >= 0 && *pbuf)
		ft_putchar_buf(pbuf, *str++);
}

t_buf	*ft_newbuf(void)
{
	t_buf	*new_buf;

	if (!(new_buf = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	if (!(new_buf->str = (char*)malloc(sizeof(char) * (size_t)PBS)))
	{
		free(new_buf);
		return (NULL);
	}
	return (new_buf);
}
