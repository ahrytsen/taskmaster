/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 10:39:21 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 10:41:30 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

static uint32_t	get_addr(void)
{
	struct hostent	*h;

	if ((h = gethostbyname(get_cconf()->addr)) == NULL)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	return (*((uint32_t *)h->h_addr));
}

int				socket_connect(void)
{
	int					sock;
	struct sockaddr_in	addr;

	ft_printf("Addr: %s\nPort: %i\n", get_cconf()->addr, get_cconf()->port);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, &(int){1}, sizeof(int)) < 0)
		ft_fatal(1, exit, "%s\n", strerror(errno));
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(get_cconf()->port ? get_cconf()->port : 7279);
	if (get_cconf()->addr && get_cconf()->type == ip)
		addr.sin_addr.s_addr = inet_addr(get_cconf()->addr);
	else if (get_cconf()->addr && get_cconf()->type == domain)
		addr.sin_addr.s_addr = get_addr();
	else
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (sock == -1)
		ft_fatal(1, exit, "%s\n", strerror(errno));
	else if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_fatal(1, exit, "%s\n", strerror(errno));
	return (sock);
}
