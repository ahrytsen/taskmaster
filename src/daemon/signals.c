/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 10:28:17 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 10:30:17 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void		sighup_handler(int sig)
{
	(void)sig;
	d_reload(NULL, get_dconf()->sockfd);
}

void			handle_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sighup_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
}
