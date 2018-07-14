/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_flags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 13:22:24 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/13 14:50:29 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void		d_usage(char *av)
{
	ft_dprintf(2,
	"taskmasterd -- run a set of applications as daemons.\n"
	"\nUsage: %s [options]\n"
	"\nOptions:\n"
	"-c -- configuration file path (searches if not given)\n"
	"-h -- print this usage message and exit\n"
	"-n -- run in the foreground (same as 'nodaemon=true' in config file)\n",
	av);
	exit(1);
}

void		check_flags(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (*av[i] == '-')
			while (*++av[i])
			{
				(*av[i] == 'h') ? d_usage(*av) : 0;
				if (*av[i] == 'n')
					get_dconf()->flags |= F_N;
				else if (*av[i] == 'c' && (get_dconf()->flags |= F_C))
				{
					get_dconf()->config_file = *++av[i] ? av[i] : av[++i];
					break ;
				}
				else
					ft_fatal(1, exit, "Error: option -%c not recognized\n"
							"For help, use %s -h\n", *av[i], *av);
			}
		else
			ft_fatal(1, exit, "Error: unexpected parameter: %s\n"
					"For help, use %s -h\n", av[i], *av);
	if ((get_dconf()->flags & F_C) && !get_dconf()->config_file)
		ft_fatal(1, exit, "Error: option -c requires argument\n"
				"For help, use %s -h\n", *av);
}
