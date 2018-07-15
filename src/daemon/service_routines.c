/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:35:53 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/15 18:25:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int is_successful(t_job *job)
{
	int		st;

	sleep(job->proc->starttime);
	if (!waitpid(job->pid, &st, WNOHANG | WUNTRACED))
	{
		pthread_mutex_lock(&get_dconf()->dmutex);
		ft_dprintf(2, "%s:%zu successfuly started\n", job->proc->name,
				   job - job->proc->jobs);
		pthread_mutex_unlock(&get_dconf()->dmutex);
		pthread_mutex_lock(&job->jmutex);
		job->ex_st = 0;
		job->status = run;
		pthread_mutex_unlock(&job->jmutex);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&get_dconf()->dmutex);
		ft_dprintf(2, "%:%zu start failed :(\n", job->proc->name,
				   job - job->proc->jobs);
		pthread_mutex_unlock(&get_dconf()->dmutex);
	}
	return (0);
}

static void	update_job_status(t_job)
{

}

static int	create_chld(t_job *job)
{
	int		p_in[2];
	int		p_out[2];
	int		p_err[2];

	if ()pipe(fd);
	if ((job->pid = fork()) > 0)
	{
		ft_dprintf(2, "%s: starting...\n", proc->name);
		job->status = start;
		time(&job->t);
	}
	else if (!proc->jobs[i].pid)
	{
		dup2(fd[0], 0);
		proc_start_chld(proc);
	}
	else
	{
		ft_asprintf(&job->error, "%s: error while fork()\n", proc->argv[0]);
	}
}

void	*proc_service(void *data)
{
	t_job	*job;
	int		i;

	job = data;
	while (1)
	{
		!(ret = is_successful(job)) && job->startretries;
		job->startretries--;
	}
	if (ret)
		waitpid(job->pid, &st, WUNTRACED);

}
