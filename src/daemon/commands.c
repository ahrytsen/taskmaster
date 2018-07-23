/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 21:06:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/19 17:34:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_exit(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_exit' called on server side: daemon will be stoped\n";
	ft_dprintf(1, "'d_exit' called: daemon will be stoped\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
	close(get_dconf()->sockfd);
	exit(0);
}

void	d_err_cmd(char **av, int sock)
{
	size_t	size;
	char	*msg;

	msg = "error: command not found: ";
	ft_dprintf(1, "error: command not found: %s\n", *av);
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = ft_strlen(*av) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, *av, size, 0);
	size = 2;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, "\n", size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}
