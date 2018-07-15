/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_stop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 18:43:41 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/15 18:16:45 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	proc_stop(t_proc *proc, int id, int sock)
{
	int		i;
	char	*line;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs + (proc->numprocs ? 0 : 1))
	{
		ft_asprintf(&line, "%s: stoping...\n", proc->name);
		proc->jobs[i].status = ST_STOP;
		proc->jobs[i].t = time(NULL);
		send_msg(sock, line);
		free(line);
		if (proc->jobs[i].pid)
			kill(proc->jobs[i].pid, proc->stopsignal);
		if (id >= 0)
			break ;
		i++;
	}
}

static void	proc_stop_byname(t_list *lst, char *name, int sock)
{
	t_proc	*proc;
	int		id;

	if ((proc = get_proc_byname(lst, name, &id)))
	{
		proc_stop(proc, id, sock);
	}
	else
	{
		send_msg(sock, name);
		send_msg(sock, ": ERROR (no such process)\n");
	}
}

void	d_stop(char **av, int sock)
{
	ft_dprintf(1, "'d_stop' called\n");
	if (!*++av)
		send_msg(sock, "Error: stop requires a process name\n");
	else
		while (*av)
			proc_stop_byname(get_dconf()->proc, *av++, sock);
	send_msg(sock, NULL);
}
