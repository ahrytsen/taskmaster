/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_restart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 17:28:38 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/20 15:49:39 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	proc_restart(t_proc *proc, int id, int sock)
{
	proc_stop(proc, id, sock);
	proc_start(proc, id, sock);
}

void		d_restart(char **av, int sock)
{
	if (!*++av)
		send_msg(sock, "Error: restart requires a process name\n");
	else if (ft_arrstr(av, "all"))
		ft_prociter(get_dconf()->proc, sock, proc_restart);
	else
		while (*av)
			proc_action_byname(get_dconf()->proc, *av++, sock, proc_restart);
	send_msg(sock, NULL);
}
