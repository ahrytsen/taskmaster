/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:06:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/23 14:09:27 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_exit(char **av, int sock)
{
	(void)av;
	ft_dprintf(1, "'daemon_exit' called: daemon will be stoped\n");
	send_msg(sock, "'daemon_exit' called on server side: "
					"daemon will be stoped\n");
	send_msg(sock, NULL);
	close(get_dconf()->sockfd);
	exit(0);
}

void	d_err_cmd(char **av, int sock)
{
	ft_dprintf(1, "error: command not found: %s\n", *av);
	send_msg(sock, "error: command not found: ");
	send_msg(sock, *av);
	send_msg(sock, "\n");
	send_msg(sock, NULL);
}
