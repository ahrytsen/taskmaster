/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 18:09:35 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_readline.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int 	send_commands(char **cmds, int sock)
{
	size_t	size;
	int 	i;
	int 	ret;
	char 	*tmp;

	i = -1;
	ret = 0;
	while (cmds[++i])
	{
		tmp = cmds[i];
		cmds[i] = ft_strtrim(cmds[i]);
		free(tmp);
		if (!ft_strncmp(cmds[i], "exit", 4))
		{
			ret = 1;
			break ;
		}
		size = ft_strlen(cmds[i]);
		send(sock, &size, sizeof(size_t), 0);
		send(sock, cmds[i], size, 0);
	}
	ft_strarr_free(cmds);
	return (ret);
}

int 	socket_connect(void)
{
	int					sock;
	struct sockaddr_in	addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("taskmasterctl: socket: ");
		return (-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7279);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("taskmasterctl: connect: ");
		return (-1);
	}
	return (sock);
}

int		main(void)
{
	char 	*line;
	int 	sock;
	char 	**cmds;

	sock = socket_connect();
	if (sock == -1)
		exit(EXIT_FAILURE);
	while (ft_readline(0, &line) > 0)
	{
		cmds = ft_strsplit(line, ';');
		free(line);
		if (cmds && send_commands(cmds, sock) == 1)
			break ;
	}
	close(sock);
	return (0);
}
