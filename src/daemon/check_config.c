/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 15:09:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/13 18:56:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int	check_jobs(t_proc *proc)
{
	int 	i;
	t_job	*job;

	i = 0;
	free(proc->jobs);
	!proc->numprocs ? (proc->numprocs = 1) : 0;
	if (!(proc->jobs = ft_memalloc(sizeof(t_job) * proc->numprocs)))
		return (-1);
	while (i < proc->numprocs)
	{
		job = proc->jobs + i++;
		time(&job->t);
	}
	return (0);
}

int			check_config(void)
{
	t_list	*lst;
	t_proc *proc;

	lst = get_dconf()->proc;
	get_dconf()->port ? 0 : (get_dconf()->port = 7279);
	while (lst)
	{
		proc = lst->content;
		if (!proc->argv && ft_dprintf(2, "Config error: you must specify the "
									  "`cmd:' for `%s' proccess\n", proc->name))
			return (-1);
		if (check_jobs(proc)
			&& ft_dprintf(2, "Error while preparing `%s' config\n", proc->name))
			return (-1);
		proc->stopsignal ? 0 : (proc->stopsignal = SIGTERM);
		lst = lst->next;
	}
	return (0);
}
