/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/07 17:01:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	main_loop(void)
{
	int		sock;
	char 	buf[2048];
	size_t	size;

	sock = accept(get_dconf()->sock_id, NULL, NULL);
	while (recv(sock, &size, sizeof(size_t), 0) > 0)
	{
		recv(sock, buf, size, 0);
		ft_dprintf(1, "%s\n", buf);
	}
	if (sock < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
	exit(0);
}

int		main(int ac, char **av)
{
	check_flags(ac, av);
	d_init();
	demonaize();
	main_loop();
}
