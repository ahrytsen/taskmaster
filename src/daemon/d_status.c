/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 23:56:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	ft_prociter(t_list *lst, int sock, void (*f)(t_proc*, int))
{
	while (lst && f)
	{
		(*f)(lst->content, sock);
		lst = lst->next;
	}
}

/* static void	proc_status_byname(t_list *lst, char *name) */
/* { */
/* 	t_proc	*proc; */

/* 	proc = lst->content; */
/* 	(void)name; */
/* } */

static void	proc_status(t_proc *proc, int sock)
{
	int		i;
	char	*line;

	i = 0;
	if (proc->numprocs > 1)
		while (i < proc->numprocs)
		{
			if (ft_asprintf(&line, "%s:%d\t\t\t%s\n", proc->name, i + 1, "lol") > 0)
				send_msg(sock, line);
		}
	else
			if (ft_asprintf(&line, "%s:%d\t\t\t%s\n", proc->name, i + 1, "lol") > 0)
				send_msg(sock, line);
}

void	d_status(char **av, int sock)
{
	char	*msg;

	ft_dprintf(1, "'d_status' called\n");
	msg = "lolka\n";
	(void)av;
	ft_prociter(get_dconf()->proc, sock, proc_status);
	send_msg(sock, NULL);
}
