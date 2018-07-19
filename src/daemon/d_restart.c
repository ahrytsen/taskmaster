/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_restart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 17:28:38 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/19 17:41:03 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_restart(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_restart' called on server side\n";
	ft_dprintf(1, "'d_restert' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}
