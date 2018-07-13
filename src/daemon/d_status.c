/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/13 19:04:43 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static char	*status_to_str(int st)
{
	if (st & ST_RUN)
		return ("RUNNING");
	else if (!st)
		return ("STOPPED");
	else if (st & ST_CRASH)
		return ("CRASHED");
	else if (st & ST_DONE)
		return ("DONE");
	else
		return ("UNKNOWN");
}

static char	*get_uptime(time_t diff)
{
	char		*tmp;
	struct tm	*res;

	res = gmtime(&diff);
	ft_asprintf(&tmp, "%.2d:%.2d:%.2d", res->tm_hour, res->tm_min, res->tm_sec);
	return (tmp);
}

static void	proc_status(t_proc *proc, int id, int sock)
{
	int			i;
	char		*line;
	char		*tmp;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs)
	{
		ft_asprintf(&tmp, proc->numprocs > 1 ? "%s:%d" : "%s", proc->name, i);
		ft_asprintf(&line, "%-30.29s%-10s", tmp,
					status_to_str(proc->jobs[i].status));
		send_msg(sock, line);
		ft_memdel((void**)&line);
		ft_memdel((void**)&tmp);
		if (proc->jobs[i].status & ST_RUN
			&& (tmp = get_uptime(time(NULL) - proc->jobs[i].t)))
			ft_asprintf(&line, "pid:%6d uptime:%9s\n", proc->jobs[i].pid, tmp);
		else
			ft_asprintf(&line, "%-.24s\n", ctime(&proc->jobs[i].t));
		send_msg(sock, line);
		ft_memdel((void**)&line);
		ft_memdel((void**)&tmp);
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
