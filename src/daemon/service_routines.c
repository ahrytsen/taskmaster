/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_routines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 22:35:53 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/23 15:01:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int	proc_watch(t_job *job)
{
	while (waitpid(job->pid, &job->ex_st, WUNTRACED) > 0)
	{
		time(&job->t);
		if (WIFSTOPPED(job->ex_st)
			&& job->proc->stopsignal == WSTOPSIG(job->ex_st))
		{
			job->status = stoping;
			ft_dprintf(1, "%s:%zu stop signal received!"
				" Program will be terminated in %d seconds\n",
				job->proc->name, job - job->proc->jobs, job->proc->stoptime);
			sleep(job->proc->stoptime);
			kill(job->pid, SIGKILL);
			waitpid(job->pid, &job->ex_st, WUNTRACED);
			return ((job->status = stop) ? 0 : 1);
		}
		if (!WIFSTOPPED(job->ex_st) && !(job->status = stop)
			&& ft_dprintf(1, "%s:%zu exited with code:%d\n", job->proc->name,
						job - job->proc->jobs, WEXITSTATUS(job->ex_st)))
			break ;
	}
	return ((job->proc->autorestart == always
			|| (job->proc->autorestart == unexp && WEXITSTATUS(job->ex_st) < 256
				&& !job->proc->exitcodes[WEXITSTATUS(job->ex_st)]))
			&& !(WIFSIGNALED(job->ex_st)
				&& WTERMSIG(job->ex_st) == job->proc->stopsignal) ? 0 : 1);
}

static int	create_chld(t_job *job)
{
	int ret;

	ret = 1;
	job->status = start;
	job->proc->stdin ? 0 : pipe(job->p_in);
	job->proc->stdout ? 0 : pipe(job->p_out);
	job->proc->stderr ? 0 : pipe(job->p_err);
	ft_memdel((void**)&job->error);
	pipe(job->service_pipe);
	if ((job->pid = fork()))
		ret = proc_start_prnt(job);
	else
	{
		job->proc->stdin ? 0 : close(job->p_in[1]);
		job->proc->stdout ? 0 : close(job->p_out[1]);
		job->proc->stderr ? 0 : close(job->p_err[1]);
		proc_start_chld(job);
	}
	return (ret);
}

static int	proc_spawn(t_job *job)
{
	int	st;

	job->start_tries = 0;
	while (job->start_tries <= job->proc->startretries)
	{
		pthread_mutex_lock(&get_dconf()->dmutex);
		ft_dprintf(1, "%s:%zu starting...(attempt %d/%d)\n", job->proc->name,
			job - job->proc->jobs, job->start_tries, job->proc->startretries);
		pthread_mutex_unlock(&get_dconf()->dmutex);
		st = create_chld(job);
		pthread_mutex_lock(&get_dconf()->dmutex);
		ft_dprintf(1, !st ? "%s:%zu successfully started (%d/%d)\n"
				: "%s:%zu start attempt failed (%d/%d)\n",
				job->proc->name, job - job->proc->jobs,
				job->start_tries, job->proc->startretries);
		pthread_mutex_unlock(&get_dconf()->dmutex);
		!st ? (job->status = run) : 0;
		job->start_tries++;
		if (!st)
			return (0);
	}
	return (-1);
}

void		*proc_service(void *data)
{
	t_job	*job;

	job = data;
	pthread_mutex_lock(&job->jmutex);
	while (!proc_spawn(job))
	{
		if (proc_watch(job))
			break ;
	}
	job->pid = 0;
	pthread_mutex_unlock(&job->jmutex);
	return (NULL);
}
