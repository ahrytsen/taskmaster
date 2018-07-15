/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 20:29:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/15 15:52:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	proc_start(t_proc *proc, int id, int sock)
{
	char	*line;
	int		i;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs + (proc->numprocs ? 0 : 1))
	{
		if (proc->jobs[i]->status == run || proc->jobs[i]->satus == start)
			ft_asprintf(&line, "ERROR: %s: olready running\n", proc->argv[0]);
		else
		{
			pthread_create(&proc->jobs[i].serv_thread, NULL, proc_service,
							proc->jobs + i);
			ft_asprintf(&line, "%s: starting...\n", proc->argv[0]);
		}
		send_msg(sock, line);
		free(line);
		if (id >= 0)
			break ;
		i++;
	}
}

void		d_start(char **av, int sock)
{
	ft_dprintf(1, "'d_start' called\n");
	if (!*++av)
		send_msg(sock, "Error: start requires a process name\n");
	else if (ft_arrstr(av, "all"))
		ft_prociter(get_dconf()->proc, sock, proc_start);
	else
		while (*av)
			proc_action_byname(get_dconf()->proc, *av++, sock, proc_start);
	send_msg(sock, NULL);
}
