/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 17:32:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	exec_cmd(char *cmd, int sock)
{
	int					i;
	char				**av;
	static const t_disp	disp[] = {{"status", d_status}, {"start", d_start},
								{"stop", d_stop}, {"restart", d_restart},
								{"reread", d_reread}, {"d_exit", d_exit},
								{NULL, d_err_cmd}};
	i = 0;
	if (!(av = ft_strsplit(cmd, ' ')))
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	while (disp[i].cmd && ft_strcmp(disp[i].cmd, *av))
		i++;
	disp[i].exec(av, sock);
}

void	main_loop(void)
{
	int		sock;
	int		ret;
	char	*cmd;
	size_t	size;

	size = 0;
	while ((sock = accept(get_dconf()->sockfd, NULL, NULL)) > 0)
	{
		while ((ret = recv(sock, &size, sizeof(size_t), 0)) > 0)
		{
			if (!(cmd = ft_memalloc(size * sizeof(char))))
				ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
			if ((ret = recv(sock, cmd, size, 0)) > 0)
				exec_cmd(cmd, sock);
			free(cmd);
		}
		if (ret < 0)
			break ;
	}
	if (sock < 0 || ret < 0)
			ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	exit(0);
}

int		main(int ac, char **av)
{
	ft_bzero(get_dconf(), sizeof(t_dconf));
	check_flags(ac, av);
	d_init();
	demonaize();
	main_loop();
 }
