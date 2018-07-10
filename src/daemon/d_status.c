/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 19:04:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	ft_prociter(t_list *lst, int sock, void (*f)(t_proc*, int))
{
	while (lst && f)
	{
		(*f)(lst, sock);
		lst = lst->next;
	}
}

static void	proc_status_byname(t_list *lst, char *name)
{
	t_proc	*proc;

	proc = lst->content;

}

static void	proc_status(t_proc *proc, int sock)
{
	int	i;

	i = 0;
	while (i < proc->numprocs)
	{
		send_msg(sock, proc->name);
		if (proc->numprocs > 1)
			send_msg(sock, :);
	}
}

void	d_status(char **av, int sock)
{
	char	*msg;

	ft_dprintf(1, "'d_status' called\n");
	msg = "lolka\n";
	(void)av;
	send_msg(sock, msg);
	send_msg(sock, NULL);
}
