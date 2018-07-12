/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/12 09:54:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static char	*status_to_str(int st)
{
	if (st & ST_RUN)
		return ("RUNNING");
	else if (st & ST_STOP)
		return ("STOPPED");
	else if (st & ST_CRASH)
		return ("CRASHED");
	else if (st & ST_DONE)
		return ("DONE");
	else
		return ("UNKNOWN");
}

static void	proc_status(t_proc *proc, int id, int sock)
{
	int		i;
	char	*line;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs + (proc->numprocs ? 0 : 1))
	{
		proc->numprocs > 1
			? ft_asprintf(&line, "%s:%d\t\t%8s\tpid:%d\tuptime: \n",
						proc->name, i, status_to_str(proc->jobs[i].status),
						proc->jobs[i].pid)
			: ft_asprintf(&line, "%s\t\t%8s\tpid:%d\tuptime: \n", proc->name,
						status_to_str(proc->jobs[i].status),
						proc->jobs[i].pid);
		send_msg(sock, line);
		free(line);
		if (id >= 0)
			break ;
		i++;
	}
}

static void	proc_status_byname(t_list *lst, char *name, int sock)
{
	t_proc	*proc;
	int		id;

	if ((proc = get_proc_byname(lst, name, &id)))
		proc_status(proc, id, sock);
	else
	{
		send_msg(sock, name);
		send_msg(sock, ": ERROR (no such process)\n");
	}

}

void	d_status(char **av, int sock)
{
	ft_dprintf(1, "'d_status' called\n");
	if (!*++av)
		ft_prociter(get_dconf()->proc, sock, proc_status);
	else
		while (*av)
			proc_status_byname(get_dconf()->proc, *av++, sock);
	send_msg(sock, NULL);
}
