/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/20 10:30:54 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void		exec_cmd(char *cmd, int sock)
{
	int					i;
	char				**av;
	static const t_disp	disp[] = {{"status", d_status}, {"start", d_start},
								{"stop", d_stop}, {"restart", d_restart},
								{"d_exit", d_exit}, {"reload", d_reload},
								{"help", d_help}, {NULL, d_err_cmd}};

	i = 0;
	if (!(av = ft_strsplit(cmd, ' ')))
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	while (disp[i].cmd && ft_strcmp(disp[i].cmd, *av))
		i++;
	disp[i].exec(av, sock);
	ft_strarr_free(av);
}

static void	*data_exchange(void *data)
{
	ssize_t	ret;
	char	*cmd;
	int		sock;

	sock = *(int *)data;
	while ((ret = receive_msg(&cmd, sock)) > 0)
	{
		exec_cmd(cmd, sock);
		free(cmd);
	}
	if (ret < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	close(sock);
	return (NULL);
}

void		main_loop(void)
{
	int			sock;
	pthread_t	p;

	while ((sock = accept(get_dconf()->sockfd, NULL, NULL)) > 0)
	{
		pthread_create(&p, NULL, data_exchange, &sock);
		pthread_detach(p);
	}
	if (sock < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	exit(0);
}

int			main(int ac, char **av)
{
	handle_signals();
	ft_bzero(get_dconf(), sizeof(t_dconf));
	check_flags(ac, av);
	d_init();
	demonaize();
	ft_prociter(get_dconf()->proc, get_dconf()->sockfd, run_autostart);
	main_loop();
}
