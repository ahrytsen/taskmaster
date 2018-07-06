/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 17:45:32 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <fcntl.h>

t_dconf	*get_donf(void)
{
	static t_dconf	dconf;

	return (&dconf);
}

void	d_init(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_bzero(get_donf(), sizeof(t_dconf));
	get_donf()->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	get_donf()->out_fd = open("taskmasterd.log", O_CREAT | O_RDWR | O_APPEND);
	get_donf()->err_fd = get_donf()->out_fd;
	if(listener < 0)
	{
		ft_dprintf(get_donf()->err_fd, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	chld_main(int ac, char **av)
{
	int		sock;
	char 	buf[2048];
	ft_bzero(&buf, 1024);
//	int		bytes_read;

	if(listener < 0)
	{
		perror("taskmasterd: socket: ");
		exit(EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("taskmasterd: bind: ");
		exit(EXIT_FAILURE);
	}
	listen(listener, 1);

	int fd = open("/Users/yvyliehz/log.txt", O_CREAT | O_WRONLY | O_APPEND);
	ft_dprintf(fd, "%s\n",getcwd(NULL, 0));
	while (1)
	{
		size_t tmp;
		sock = accept(listener, NULL, NULL);
		if (recv(sock, &tmp, sizeof(size_t), 0))
			ft_dprintf(fd, "%zu\n", tmp);
	};
	//p==-1 ? dprintf(fd, "%s\n", strerror(errno)) : dprintf (fd, "%d", p);
	exit(0);
}

int		main(int ac, char **av)
{
	pid_t	p;


	if ((p = fork()) > 0)
		ft_printf("taskmaster: *Daemon started successully* [pid: %d]\n", p);
	else if (!p)
	{
		close(0);
		close(1);
		close(2);
		setsid();
		umask(0);
		chld_main(ac, av);
	}
	else
		perror("(ERROR)taskmaster");

	exit(p > 0 ? 0 : 1);
}
