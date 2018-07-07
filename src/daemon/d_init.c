/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:37:05 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/07 16:06:42 by ahrytsen         ###   ########.fr       */
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
	if ((get_dconf()->sock_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	get_dconf()->addr.sin_family = AF_INET;
	get_dconf()->addr.sin_port = htons(7279);
	get_dconf()->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(get_dconf()->sock_id, (struct sockaddr *)&get_dconf()->addr,
			sizeof(get_dconf()->addr)) < 0
		|| listen(get_dconf()->sock_id, 1) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
}

t_dconf		*get_dconf(void)
{
	static t_dconf	dconf;

	return (&dconf);
}

void		demonaize(void)
{
	if (!(get_dconf()->flags & F_N) && (get_dconf()->pid = fork()) > 0)
		ft_printf("taskmaster: *Daemon started successully* [pid: %d]\n",
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
	ft_printf("taskmaster: *Daemon started successully* [pid: %d]\n",
			  get_dconf()->pid);
}

void		d_init(void)
{
	close(0);
	!get_dconf()->config_file
		? get_dconf()->config_file = "taskmasterd.conf" : 0;
	get_dconf()->out_log = "tmd_out.log";
	get_dconf()->err_log = "tmd_err.log";
	open_logs();
	prepare_socket();
}