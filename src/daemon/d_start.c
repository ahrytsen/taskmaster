/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 20:29:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/23 14:31:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	proc_start(t_proc *proc, int id, int sock)
{
	char	*line;
	int		i;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs + (proc->numprocs ? 0 : 1))
	{
		line = NULL;
		if (proc->jobs[i].pid)
			id >= 0 ? ft_asprintf(&line, "ERROR: %s:%d already running\n",
								proc->name, i) : 0;
		else
		{
			pthread_create(&proc->jobs[i].serv_thread, NULL, proc_service,
							proc->jobs + i);
			pthread_detach(proc->jobs[i].serv_thread);
			id >= 0 ? ft_asprintf(&line, "%s:%d starting...\n",
							proc->name, i) : 0;
		}
		line && sock >= 0 ? send_msg(sock, line) : 0;
		free(line);
		if (id >= 0)
			break ;
		i++;
	}
}

void	d_start(char **av, int sock)
{
	if (!*++av)
		send_msg(sock, "Error: start requires a process name\n");
	else if (ft_arrstr(av, "all"))
		ft_prociter(get_dconf()->proc, sock, proc_start);
	else
		while (*av)
			proc_action_byname(get_dconf()->proc, *av++, sock, proc_start);
	send_msg(sock, NULL);
}
