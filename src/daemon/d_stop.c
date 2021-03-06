/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_stop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 18:43:41 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/20 15:49:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	proc_stop(t_proc *proc, int id, int sock)
{
	int		i;
	char	*line;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs)
	{
		line = NULL;
		if (proc->jobs[i].pid)
		{
			kill(proc->jobs[i].pid, proc->stopsignal);
			if (id >= 0)
				ft_asprintf(&line, "%s:%d stopping...\n", proc->name, i);
		}
		else if (id >= 0)
			ft_asprintf(&line, "ERROR: %s:%d already stopped\n", proc->name, i);
		line && sock >= 0 ? send_msg(sock, line) : 0;
		free(line);
		pthread_mutex_lock(&proc->jobs[i].jmutex);
		pthread_mutex_unlock(&proc->jobs[i].jmutex);
		if (id >= 0)
			break ;
		i++;
	}
}

void	d_stop(char **av, int sock)
{
	if (!*++av)
		send_msg(sock, "Error: stop requires a process name\n");
	else if (ft_arrstr(av, "all"))
		ft_prociter(get_dconf()->proc, sock, proc_stop);
	else
		while (*av)
			proc_action_byname(get_dconf()->proc, *av++, sock, proc_stop);
	send_msg(sock, NULL);
}
