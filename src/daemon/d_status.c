/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/19 17:26:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static char	*status_to_str(enum e_status st)
{
	if (st == run)
		return ("RUNNING");
	else if (st == stop)
		return ("STOPPED");
	else if (st == stoping)
		return ("STOPPING");
	else if (st == crash)
		return ("CRASHED");
	else if (st == done)
		return ("DONE");
	else if (st == fail)
		return ("FAILED");
	else if (st == fatal)
		return ("FATAL");
	else if (st == start)
		return ("STARTING");
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

	i = (id < 0 ? 0 : id);
	while (i < proc->numprocs && (id >= 0 ? i == id : 1))
	{
		ft_asprintf(&tmp, proc->numprocs > 1 ? "%s:%d" : "%s", proc->name, i);
		ft_asprintf(&line, "%-*s%-10s", get_dconf()->max_namelen + 3, tmp,
					status_to_str(proc->jobs[i].status));
		send_msg(sock, line);
		ft_memdel((void**)&line);
		ft_memdel((void**)&tmp);
		if (proc->jobs[i].status == run
			&& (tmp = get_uptime(time(NULL) - proc->jobs[i].t)))
			ft_asprintf(&line, "pid%6d, uptime%9s\n", proc->jobs[i].pid, tmp);
		else
			proc->jobs[i].status == fatal || proc->jobs[i].status == fail
				? ft_asprintf(&line, "%s\n", proc->jobs[i].error)
				: ft_asprintf(&line, "%-.24s\n", ctime(&proc->jobs[i].t));
		send_msg(sock, line);
		ft_memdel((void**)&line);
		ft_memdel((void**)&tmp);
		i++;
	}
}

void		d_status(char **av, int sock)
{
	if (!*++av || ft_arrstr(av, "all"))
		ft_prociter(get_dconf()->proc, sock, proc_status);
	else
		while (*av)
			proc_action_byname(get_dconf()->proc, *av++, sock, proc_status);
	send_msg(sock, NULL);
}
