/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_max_proclen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 10:24:59 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 10:27:03 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

int		count_max_proclen(t_list *proc)
{
	int		namelen;
	int		tmp;

	namelen = 0;
	while (proc)
	{
		((t_proc *)proc->content)->numprocs
		? 0 : ((t_proc *)proc->content)->numprocs++;
		tmp = ft_strlen(((t_proc *)proc->content)->name);
		if (((t_proc *)proc->content)->numprocs > 1)
			tmp += ft_count_digits(((t_proc *)proc->content)->numprocs - 1) + 1;
		tmp > namelen ? (namelen = tmp) : 0;
		proc = proc->next;
	}
	return (namelen);
}
