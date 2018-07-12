/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 20:29:07 by ahrytsen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/07/12 10:25:45 by ahrytsen         ###   ########.fr       */
=======
/*   Updated: 2018/07/12 14:55:49 by ahrytsen         ###   ########.fr       */
>>>>>>> dev_ahrytsen
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	proc_start(t_proc *proc, int id, int sock)
{
	int		i;
	int		fd[2];
	char	*line;

	i = id < 0 ? 0 : id;
	while (i < proc->numprocs + (proc->numprocs ? 0 : 1))
	{
		pipe(fd);
		if ((proc->jobs[i].pid = fork()) > 0)
<<<<<<< HEAD
			ft_asprintf(&line, "");
=======
		{
			ft_asprintf(&line, "%s: starting...\n", proc->argv[0]);
			proc->jobs[i].status = ST_RUN;
		}
		else if (!proc->jobs[i].pid)
		{
			dup2(fd[0], 0);
			proc_start_chld(proc);
		}
		else
			ft_asprintf(&line, "%s: error while fork()\n", proc->argv[0]);
>>>>>>> dev_ahrytsen
		send_msg(sock, line);
		free(line);
		if (id >= 0)
			break ;
		i++;
	}
}

static void	proc_start_byname(t_list *lst, char *name, int sock)
{
	t_proc	*proc;
	int		id;

	if ((proc = get_proc_byname(lst, name, &id)))
	{
		proc_start(proc, id, sock);
	}
	else
	{
		send_msg(sock, name);
		send_msg(sock, ": ERROR (no such process)\n");
	}
}

void	d_start(char **av, int sock)
{
	ft_dprintf(1, "'d_start' called\n");
	if (!*++av)
		send_msg(sock, "Error: start requires a process name\n");
	else
		while (*av)
			proc_start_byname(get_dconf()->proc, *av++, sock);
	send_msg(sock, NULL);
}
