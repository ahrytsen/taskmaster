/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12:07:48 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/13 19:02:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

t_proc	*get_proc_byname(t_list *proc, char *name, int *id)
{
	char	*tmp;
	t_proc	*ret;
	int		id_tmp;

	(tmp = ft_strchr(name, ':')) ? (*tmp = '\0') : 0;
	if ((id_tmp = -2) && tmp && (!*(tmp + 1) || ft_strequ(tmp + 1, "*")))
		id_tmp = -1;
	else if (tmp)
		ft_isnumeric_str(tmp + 1) ? (id_tmp = ft_atoi(tmp + 1))
			: (int)(proc = NULL);
	while (proc && (ret = proc->content))
	{
		if (ft_strequ(ret->name, name))
		{
			if ((ret->numprocs < 2 && id_tmp >= 0)
				|| (ret->numprocs > 1 && id_tmp == -2)
				|| id_tmp >= ret->numprocs + (ret->numprocs ? 0 : 1))
				ret = NULL;
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

void	proc_start_chld(t_proc *proc)
{
	pid_t		pid;
	extern char	**environ;

	pid = getpid();
	signal(SIGCHLD, SIG_DFL); //del
	setpgid(pid, pid);
	execve(proc->argv[0], proc->argv, environ);
	exit(1);
}
