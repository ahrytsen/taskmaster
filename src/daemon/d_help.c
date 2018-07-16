/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_help.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:04:01 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/16 11:18:21 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void			d_help(char **av, int sock)
{
	ft_printf("d_help called\n");
	(void)av;
	send_msg(sock, "======================================================\n"
					"d_exit\t\texit\t\treload\t\treread\n"
					"reload\t\trestart\t\tstart\t\tstatus\n"
					"stop\n"
					"======================================================\n");
	send_msg(sock, NULL);
}
