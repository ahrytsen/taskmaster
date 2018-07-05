/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:28:37 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 17:04:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

ssize_t	ft_read(int fd, uint64_t *buf)
{
	ssize_t	ret;

	*buf = 0;
	ret = read(fd, buf, 1);
	if (ret != 1 || (*buf <= 0x7F && *buf != 0x1B))
		return (ret);
	else if (*buf == 0x1B)
		ret = read(fd, (uint8_t*)buf + 1, 6);
	else if (*buf >= 0xC2 && *buf <= 0xDF)
		ret = read(fd, (uint8_t*)buf + 1, 1);
	else if (*buf >= 0xE0 && *buf <= 0xEF)
		ret = read(fd, (uint8_t*)buf + 1, 2);
	else if (*buf >= 0xF0 && *buf <= 0xF4)
		ret = read(fd, (uint8_t*)buf + 1, 3);
	return (ret > 0 ? ret + 1 : ret);
}
