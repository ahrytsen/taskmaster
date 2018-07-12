/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12:07:48 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/12 10:07:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

t_proc	*get_proc_byname(t_list *proc, char *name, int *id)
{
	char	*tmp;
	t_proc	*ret;

	(tmp = ft_strchr(name, ':')) ? (*tmp = '\0') : 0;
	*id = -2;
	if (tmp && (!*(tmp + 1) || ft_strequ(tmp + 1, "*")))
		*id = -1;
	else if (tmp)
		ft_isnumeric_str(tmp + 1) ? (*id = ft_atoi(tmp + 1))
			: (int)(proc = NULL);
	while (proc && (ret = proc->content))
	{
		if (ft_strequ(ret->name, name))
		{
			if ((ret->numprocs < 2 && *id >= 0)
				|| (ret->numprocs > 1 && *id == -2)
				|| *id >= ret->numprocs + (ret->numprocs ? 0 : 1))
				ret = NULL;
			break ;
		}
		proc = proc->next;
	}
	tmp ? (*tmp = ':') : 0;
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

//void	proc_start_chld(t_proc *proc)
//{
//
//}
