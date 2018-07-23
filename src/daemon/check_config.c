/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 15:09:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/21 12:29:18 by yvyliehz         ###   ########.fr       */
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
		job->proc = proc;
		time(&job->t);
		if (pthread_mutex_init(&job->jmutex, NULL)
			&& ft_dprintf(1, "%s:%2d: mutex init failed\n", proc->name, i))
			return (-1);
	}
	return (0);
}

int			check_config(t_dconf *conf)
{
	t_list	*lst;
	t_proc	*proc;

	lst = conf->proc;
	conf->port ? 0 : (conf->port = 7279);
	if (pthread_mutex_init(&conf->dmutex, NULL)
		&& ft_dprintf(1, "%s: mutex init failed\n", "daemon config"))
		return (-1);
	while (lst)
	{
		proc = lst->content;
		if ((!proc->argv && ft_dprintf(1, "Config error: you must specify the "
									"`cmd:' for `%s' proccess\n", proc->name))
			|| (check_jobs(proc)
				&& ft_dprintf(1, "%s: error while checking job\n", proc->name)))
			return (-1);
		proc->stopsignal ? 0 : (proc->stopsignal = SIGTERM);
		lst = lst->next;
	}
	!conf->out_log ? conf->out_log = ft_strdup("taskmasterd.out") : 0;
	!conf->email ? conf->email = ft_strdup(getenv("MAIL")) : 0;
	!conf->email ? conf->email = ft_strdup(getenv("USER")) : 0;
	return (0);
}
