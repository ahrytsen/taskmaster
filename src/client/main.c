/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/14 19:22:34 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

t_cconf		*get_cconf(void)
{
	static t_cconf	cconf;

	return (&cconf);
}

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

static uint32_t	get_addr()
{
	struct hostent	*h;

	if ((h = gethostbyname(get_cconf()->addr)) == NULL)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	return (*((uint32_t *)h->h_addr));
}

int		socket_connect(void)
{
	int					sock;
	struct sockaddr_in	addr;

	ft_printf("Addr: %s\nPort: %i\n", get_cconf()->addr, get_cconf()->port);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(get_cconf()->port ? get_cconf()->port : 7279);
	if (get_cconf()->addr && get_cconf()->type == ip)
		addr.sin_addr.s_addr = inet_addr(get_cconf()->addr);
	else if (get_cconf()->addr && get_cconf()->type == domain)
		addr.sin_addr.s_addr = get_addr();
	else
		addr.sin_addr.s_addr = INADDR_LOOPBACK;
	if (sock == -1)
		ft_fatal(1, exit, "%s\n", strerror(errno));
	else if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_fatal(1, exit, "%s\n", strerror(errno));
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

int		main(int ac, char **av)
{
	char	*line;
	int		sock = 0;
	char	**cmds;

	ft_bzero(get_cconf(), sizeof(t_cconf));
	check_flags(ac, av);
	sock = socket_connect();
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
