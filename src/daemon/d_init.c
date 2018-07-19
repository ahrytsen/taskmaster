/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:37:05 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/19 15:50:40 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	open_logs(void)
{
	if (!(get_dconf()->flags & F_N))
	{
		get_dconf()->out_fd = open(get_dconf()->out_log,
								O_CREAT | O_RDWR | O_APPEND,
								S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		get_dconf()->err_fd = get_dconf()->err_log
			? open(get_dconf()->err_log, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
			: get_dconf()->out_fd;
	}
}

static void	prepare_socket(void)
{
	if ((get_dconf()->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_fatal(EXIT_FAILURE, exit, "socket: %s\n", strerror(errno));
	if (setsockopt(get_dconf()->sockfd, SOL_SOCKET, SO_REUSEADDR,
			&(int){1}, sizeof(int)) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	if (setsockopt(get_dconf()->sockfd, SOL_SOCKET, SO_NOSIGPIPE,
				   &(int){1}, sizeof(int)) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	get_dconf()->addr.sin_family = AF_INET;
	get_dconf()->addr.sin_port = htons(get_dconf()->port
									? get_dconf()->port : 7279);
	if (get_dconf()->ip)
		get_dconf()->addr.sin_addr.s_addr = inet_addr(get_dconf()->ip);
	else
		get_dconf()->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(get_dconf()->sockfd, (struct sockaddr *)&get_dconf()->addr,
			sizeof(get_dconf()->addr)) < 0
		|| listen(get_dconf()->sockfd, 1) < 0)
		ft_fatal(EXIT_FAILURE, exit, "socket: %s\n", strerror(errno));
}

t_dconf		*get_dconf(void)
{
	static t_dconf	dconf;

	return (&dconf);
}

void		demonaize(void)
{
	if (!(get_dconf()->flags & F_N) && (get_dconf()->pid = fork()) > 0)
		ft_printf("taskmaster: *Daemon started successfully* [pid: %d]\n",
				get_dconf()->pid);
	else if (!get_dconf()->pid && !(get_dconf()->flags & F_N))
	{
		dup2(get_dconf()->out_fd, 1);
		dup2(get_dconf()->err_fd, 2);
		setsid();
		umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else if (get_dconf()->pid == -1)
		perror("(ERROR)taskmaster");
	if (get_dconf()->pid)
		exit(get_dconf()->pid == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
	get_dconf()->pid = getpid();
	ft_printf("taskmaster: *Daemon started successfully* [pid: %d]\n",
			get_dconf()->pid);
}

void		d_init(void)
{
	close(0);
	parse_config(get_dconf());
	open_logs();
	prepare_socket();
}
