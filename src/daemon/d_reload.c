/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:43:03 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/15 18:50:45 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_reload(char **av, int sock)
{
	ft_printf("'d_reload' called\n");
	(void)av;
	ft_prociter(get_dconf()->proc, sock, proc_stop);
	ft_lstdel(&get_dconf()->proc, free_config_proc);
	parse_config();
	send_msg(sock, NULL);
}