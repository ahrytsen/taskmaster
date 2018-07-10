/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:02:43 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 17:04:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_status(char **av, int sock)
{
	char	*msg;

	ft_dprintf(1, "'d_status' called\n");

	send_msg(sock, msg);
	send_msg(sock, NULL);
}
