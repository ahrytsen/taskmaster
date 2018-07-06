/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 18:18:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>


t_dconf	*get_dconf(void)
{
	static t_dconf	dconf;

	return (&dconf);
}

void	d_init(int ac, char **av)
{
	(void)ac;
	(void)av;
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

void	chld_main(int ac, char **av)
{
	int		sock;
	char 	buf[2048];
	size_t	size;

	d_init(ac, av);
	while ((sock = accept(get_dconf()->sock_id, NULL, NULL)) > 0)
	{
		if (recv(sock, &size, sizeof(size_t), 0)
			&& recv(sock, &buf, size, 0))
			ft_dprintf(get_dconf()->out_fd, "%s\n", buf);
	}
	if (sock < 0)
		ft_dprintf(get_dconf()->err_fd, "%s\n", strerror(errno));
	exit(sock < 0 ? 1 : 0);
}

int		main(int ac, char **av)
{
	pid_t	p;

	ft_bzero(get_dconf(), sizeof(t_dconf));
	get_dconf()->config_file = "taskmasterd.log";
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
