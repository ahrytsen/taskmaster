/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:35:53 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/16 21:19:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int	proc_watch(t_job *job)
{
	int	st;

	while (waitpid(job->pid, &st, WUNTRACED))
	{
		pthread_mutex_lock(&job->jmutex);
		job->ex_st = st;
		pthread_mutex_unlock(&job->jmutex);
		if (WIFEXITED(st))
			break ;
	}
	st < 256 && job->proc->exitcodes[st]
}

static int	create_chld(t_job *job)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&job->proc->pmutex);
	pthread_mutex_lock(&job->jmutex);
	job->status = start;
	job->proc->stdin ? 0 : pipe(job->p_in);
	job->proc->stdout ? 0 : pipe(job->p_out);
	job->proc->stderr ? 0 : pipe(job->p_err);
	ft_memdel((void**)&job->error);
	pipe(get_dconf()->service_pipe);
	if ((job->pid = fork()))
		ret = proc_start_prnt(job);
	else
		proc_start_chld(job);
	pthread_mutex_unlock(&job->jmutex);
	pthread_mutex_unlock(&job->proc->pmutex);
	return (ret);
}

static int proc_spawn(t_job *job)
{
	int	st;
	int	i;

	i = 0;
	while (i++ <= job->proc->startretries)
	{
		st = create_chld(job);
		pthread_mutex_lock(&get_dconf()->dmutex);
		pthread_mutex_lock(&job->jmutex);
		!st ? ft_dprintf(2, "%s:%zu successfuly started\n", job->proc->name,
						job - job->proc->jobs)
			: ft_dprintf(2, "%:%zu start failed :(\n", job->proc->name,
						job - job->proc->jobs);
		job->status = !st ? run : fail;
		pthread_mutex_unlock(&job->jmutex);
		pthread_mutex_unlock(&get_dconf()->dmutex);
		if (!st)
			return (0);
	}
	return (-1);
}

void	*proc_service(void *data)
{
	t_job	*job;
	int		st;

	job = data;
	while (!proc_spawn(job))
	{

		if (proc_watch(job))
			break ;
	}
	return (NULL);
}
