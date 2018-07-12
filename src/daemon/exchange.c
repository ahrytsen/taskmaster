/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exchange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:10:59 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 17:36:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	send_msg(int sock, char	*msg)
{
	size_t	size;

	size = msg ? (ft_strlen(msg) + 1) : 0;
	send(sock, &size, sizeof(size_t), 0);
	size ? send(sock, msg, size, 0) : 0;
}

/* char	*recive_msg(int sock) */
/* { */
/* 	char	*msg; */
/* 	size_t	size; */

/* 	msg = NULL; */
/* 	if ((ret = recv(sock, &size, sizeof(size_t), 0)) > 0) */
/* 	{ */
/* 	if (!(msg = ft_memalloc(size * sizeof(char)))) */
/* 		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno)); */
/* 	if ((ret = recv(sock, cmd, size, 0)) > 0) */
/* 		exec_cmd(cmd, sock); */
/* } */
