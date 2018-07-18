/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exchange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:10:59 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/17 10:02:21 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	send_msg(int sock, char *msg)
{
	size_t	size;

	size = msg ? (ft_strlen(msg) + 1) : 0;
	send(sock, &size, sizeof(size_t), 0);
	if (size)
		send(sock, msg, size, 0);
}

ssize_t	receive_msg(char **line, int sock)
{
	size_t	size;
	ssize_t	ret;

	*line = NULL;
	if ((ret = recv(sock, &size, sizeof(size_t), 0)) > 0)
	{
		if (!(*line = ft_memalloc(size * sizeof(char))))
			ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
		if ((ret = recv(sock, *line, size, 0)) <= 0)
			ft_memdel((void**)line);
	}
	return (ret);
}
