/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 20:57:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_usage(char *av)
{
	ft_dprintf(2,
	"taskmasterd -- run a set of applications as daemons.\n"
	"\nUsage: %s [options]\n"
	"\nOptions:\n"
	"-c -- configuration file path (searches if not given)\n",
	"-h -- print this usage message and exit\n"
	"-n -- run in the foreground (same as 'nodaemon=true' in config file)\n",
	av);
	exit(1);
}

t_dconf	*get_dconf(void)
{
	static t_dconf	dconf;

	return (&dconf);
}

void	d_init(void)
{
	get_dconf()->config_file = "file.log";
	get_dconf()->out_fd = open(get_dconf()->config_file,
							O_CREAT | O_RDWR | O_APPEND);
	get_dconf()->err_fd = get_dconf()->out_fd;
	if ((get_dconf()->sock_id = socket(AF_INET, SOCK_STREAM, 0)) < 0
		&& ft_dprintf(get_dconf()->err_fd, "%s\n", strerror(errno)))
		exit(EXIT_FAILURE);
	get_dconf()->addr.sin_family = AF_INET;
	get_dconf()->addr.sin_port = htons(7279);
	get_dconf()->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(get_dconf()->sock_id, (struct sockaddr *)&get_dconf()->addr,
			sizeof(get_dconf()->addr)) < 0 || listen(get_dconf()->sock_id, 1) < 0)
		&& ft_dprintf(get_dconf()->err_fd, "%s\n", strerror(errno)))
		exit(EXIT_FAILURE);
}

void	check_flags(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (*av[i] == '-')
			while (1)
			{

			}
		else
		{
			ft_dprintf(2, "taskmasterd: unexpected parameter: %s\n", av[i]);
			d_usage(*av);
		}
	}
}

void	chld_main(void)
{
	int		sock;
	char 	buf[2048];
	size_t	size;

	sock = accept(get_dconf()->sock_id, NULL, NULL);
	while (1)
	{
		if (recv(sock, &size, sizeof(size_t), 0) > 0)
		{
			recv(sock, buf, size, 0);
			ft_dprintf(get_dconf()->out_fd, "%s\n", buf);
		}
		else
			break ;
	}
	if (sock < 0)
		ft_dprintf(get_dconf()->err_fd, "%s\n", strerror(errno));
	exit(sock < 0 ? 1 : 0);
}

int		main(int ac, char **av)
{
	pid_t	p;

	check_flags(ac, av);
	d_init();
	if ((p = fork()) > 0)
		ft_printf("taskmaster: *Daemon started successully* [pid: %d]\n", p);
	else if (!p)
	{
		close(0);
		close(1);
		close(2);
		setsid();
		umask(S_IWGRP | S_IWOTH);
		chld_main();
	}
	else
		perror("(ERROR)taskmaster");

	exit(p > 0 ? 0 : 1);
}
