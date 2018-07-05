/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 20:15:18 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 21:55:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	chld_main(int ac, char **av)
{
	(void)ac;
	(void)av;
	close(0);
    close(1);
    close(2);
	setsid();
	while (1);
	//p==-1 ? dprintf(fd, "%s\n", strerror(errno)) : dprintf (fd, "%d", p);
	exit (0);
}

int		main(int ac, char **av)
{
	pid_t	p;

	if ((p = fork()) > 0)
		ft_printf("taskmaster: *Daemon started successully* [pid: %d]\n", p);
	else if (!p)
		chld_main(ac, av);
	else
		perror("(ERROR)taskmaster");
	exit(p > 0 ? 0 : 1);
}
