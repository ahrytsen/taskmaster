/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 15:09:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/14 21:53:40 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int	check_jobs(t_proc *proc)
{
	int		i;
	t_job	*job;

	i = -1;
	free(proc->jobs);
	!proc->starttime ? (proc->starttime = 1) : 0;
	!proc->numprocs ? (proc->numprocs = 1) : 0;
	if (!(proc->jobs = ft_memalloc(sizeof(t_job) * proc->numprocs)))
		return (-1);
	while (++i < proc->numprocs)
	{
		job = proc->jobs + i;
		job->startretries = proc->startretries;
		job->proc = proc;
		time(&job->t);
		if (pthread_mutex_init(&job->jmutex, NULL)
			&& ft_dprintf(2, "%s:%2d: mutex init failed\n", proc->name, i))
			return (-1);
	}
	return (0);
}

int			check_config(void)
{
	t_list	*lst;
	t_proc	*proc;

	lst = get_dconf()->proc;
	get_dconf()->port ? 0 : (get_dconf()->port = 7279);
	if (pthread_mutex_init(&get_dconf()->dmutex, NULL)
		&& ft_dprintf(2, "%s: mutex init failed\n", "daemon config"))
		return (-1);
	while (lst)
	{
		proc = lst->content;
		if ((!proc->argv && ft_dprintf(2, "Config error: you must specify the "
									"`cmd:' for `%s' proccess\n", proc->name))
			|| (pthread_mutex_init(&proc->pmutex, NULL)
				&& ft_dprintf(2, "%s: mutex init failed\n", "daemon config"))
			|| (check_jobs(proc)
				&& ft_dprintf(2, "%s: error while checking job\n", proc->name)))
			return (-1);
		proc->stopsignal ? 0 : (proc->stopsignal = SIGTERM);
		lst = lst->next;
	}
	return (0);
}
