/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:35:53 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/14 22:39:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int is_successful(t_job *job)
{
	while (1)
	{
		sleep(job->proc->starttime);
		if (!waitpid(job->pid, &st, WNOHANG | WUNTRACED))
		{
			pthread_mutex_lock(&get_dconf()->dmutex);
			ft_dprintf(2, "%s:%.2zu successfuly started\n", job->proc->name,
						job - job->proc->jobs);
			pthread_mutex_unlock(&get_dconf()->dmutex);
			pthread_mutex_lock(&job->jmutex);
			job->ex_st = st;
			job->status = run;
			pthread_mutex_unlock(&job->jmutex);
			return (1);
		}
		else
		{
			pthread_mutex_lock(&get_dconf()->dmutex);
			ft_dprintf(2, "%:%.2zu start failed :(\n", job->proc->name,
						job - job->proc->jobs);
			pthread_mutex_unlock(&get_dconf()->dmutex);
			if (job->startretries-- > 0)
				continue ;
		}
	}
	return (0);
}

void	*wait_routine(void *data)
{
	t_job	*job;
	int		st;

	job = data;
	while (1)
	{


	}
	if (!st)
		waitpid(job->pid, &st, WUNTRACED);
//	pthread_exit(&job->ex_st);
	return (NULL);
}
