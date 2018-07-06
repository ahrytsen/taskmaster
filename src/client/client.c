/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 13:46:50 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_readline.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int		main(void)
{
	int 	sock;
	size_t 	size;
	struct	sockaddr_in addr;
	char	*line;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("taskmasterctl: socket: ");
		exit(EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("taskmasterctl: connect: ");
		exit(EXIT_FAILURE);
	}
	while (ft_readline(0, &line) > 0)
	{
		ft_printf("line: %s\n", line);
		size = ft_strlen(line);
		send(sock, &size, sizeof(size_t), 0);
//		ft_printf("send_ret: %i\n", send(sock, line, ft_strlen(line), 0));
//		recv(sock, , 1024, 0);
//		ft_printf("recieved: %s\n", buf);
		free(line);
	}
}

// 0 - ctrl + D
// -1 - Error
