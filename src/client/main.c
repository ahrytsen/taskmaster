/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/12 20:01:46 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void	get_response(int sock)
{
	int		ret;
	size_t	size;
	char	*msg;

	while ((ret = recv(sock, &size, sizeof(size_t), 0)) > 0 && size > 0)
	{
		if (!(msg = ft_memalloc(size * sizeof(char))))
			ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
		if ((ret = recv(sock, msg, size, 0)) > 0)
			ft_dprintf(1, "%s", msg);
		free(msg);
	}
	if (ret < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
}

int		socket_connect(void)
{
	int					sock;
	struct sockaddr_in	addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7278);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (sock == -1)
		perror("taskmasterctl: socket");
	else if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("taskmasterctl: connect");
		return (-1);
	}
	return (sock);
}

int		send_commands(char **cmds, int sock)
{
	size_t	size;
	int		i;
	int		ret;
	char	*tmp;

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
		size = ft_strlen(cmds[i]) + 1;
		send(sock, &size, sizeof(size_t), 0);
		send(sock, cmds[i], size, 0);
		get_response(sock);
	}
	ft_strarr_free(cmds);
	return (ret);
}

int		main(void)
{
	char	*line;
	int		sock;
	char	**cmds;

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
