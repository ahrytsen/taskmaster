/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 20:23:13 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/23 13:18:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

t_proc	*get_proc_byname(t_list *proc, char *name, int *id)
{
	char	*tmp;
	t_proc	*ret;
	int		id_tmp;

	tmp = ft_strchr(name, ':');
	id_tmp = -2;
	if (tmp && !(*tmp = '\0') && (!*(tmp + 1) || ft_strequ(tmp + 1, "*")))
		id_tmp = -1;
	else if (tmp)
		ft_isnumeric_str(tmp + 1) ? (id_tmp = ft_atoi(tmp + 1))
			: (int)(proc = NULL);
	while (proc && (ret = proc->content))
	{
		if (ft_strequ(ret->name, name))
		{
			(id_tmp >= ret->numprocs || (ret->numprocs == 1 && id_tmp >= 0)
			|| (ret->numprocs > 1 && id_tmp == -2)) ? (ret = NULL) : NULL;
			break ;
		}
		proc = proc->next;
	}
	tmp ? (*tmp = ':') : 0;
	id ? (*id = id_tmp) : 0;
	return (!proc ? NULL : ret);
}

void	ft_prociter(t_list *lst, int sock, void (*f)(t_proc*, int, int))
{
	while (lst && f)
	{
		(*f)(lst->content, -1, sock);
		lst = lst->next;
	}
}

int		proc_start_prnt(t_job *job)
{
	job->proc->stdin ? 0 : close(job->p_in[0]);
	job->proc->stdout ? 0 : close(job->p_out[0]);
	job->proc->stderr ? 0 : close(job->p_err[0]);
	close(job->service_pipe[1]);
	time(&job->t);
	if (job->pid < 0 && !(job->pid = 0)
		&& ft_asprintf(&job->error, "%s:%zu: error while fork()",
					job->proc->name, job - job->proc->jobs))
	{
		!job->proc->stdin ? close(job->p_in[1]) : 0;
		!job->proc->stdout ? close(job->p_out[1]) : 0;
		!job->proc->stderr ? close(job->p_err[1]) : 0;
	}
	else
		sleep(job->proc->starttime ? job->proc->starttime : 1);
	if (job->pid > 0 && waitpid(job->pid, &job->ex_st, WNOHANG) > 0)
	{
		job->status = fail;
		if (get_next_line(job->service_pipe[0], &job->error) > 0)
			job->status = fatal;
		job->pid = 0;
	}
	close(job->service_pipe[0]);
	return (job->pid > 0 ? 0 : -1);
}

void	proc_start_chld(t_job *job)
{
	pid_t	pid;

	pid = getpid();
	job->proc->workingdir ? chdir(job->proc->workingdir) : 0;
	close(job->service_pipe[0]);
	while (job->proc->env && *(job->proc->env))
		putenv(*(job->proc->env)++);
	setpgid(pid, pid);
	if (job->proc->stdin)
		job->p_in[0] = open(job->proc->stdin, O_RDONLY);
	dup2(job->p_in[0], 0);
	if (job->proc->stdout)
		job->p_out[0] = open(job->proc->stdout, O_CREAT | O_WRONLY | O_APPEND,
							job->proc->umask);
	dup2(job->p_out[0], 1);
	if (job->proc->stderr)
		job->p_err[0] = open(job->proc->stderr, O_CREAT | O_WRONLY | O_APPEND,
							job->proc->umask);
	dup2(job->p_err[0], 2);
	fcntl(job->service_pipe[1], F_SETFD, FD_CLOEXEC);
	execvp(job->proc->argv[0], job->proc->argv);
	ft_dprintf(job->service_pipe[1], "%s: %s", job->proc->cmd, strerror(errno));
	abort();
}

void	proc_action_byname(t_list *lst, char *name, int sock,
							void (*action)(t_proc*, int, int))
{
	t_proc	*proc;
	int		id;

	if ((proc = get_proc_byname(lst, name, &id)))
	{
		id == -2 ? (id = 0) : 0;
		action(proc, id, sock);
	}
	else
	{
		send_msg(sock, name);
		send_msg(sock, ": ERROR (no such process)\n");
	}
}
