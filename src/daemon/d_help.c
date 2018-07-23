/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_help.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:04:01 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 18:12:18 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

const static t_help	g_cmds[] =
{
	{"exit", "Exit the taskmaster shell.\n"},
	{"reload", "Restart the remote supervisord.\n"},
	{"restart", "restart <name>\t\tRestart a process\n"
		"restart <gname>:*\tRestart all processes in a group\n"
		"restart <name> <name>\tRestart multiple processes or groups\n"
		"restart all\t\tRestart all processes\n"
		"Note: restart does not reread config files. For that, see reload.\n"},
	{"start", "start <name>\t\tStart a process\n"
		"start <gname>:*\t\tStart all processes in a group\n"
		"start <name> <name>\tStart multiple processes or groups\n"
		"start all\t\tStart all processes\n"},
	{"status", "status <name>\t\tGet status for a single process\n"
		"status <gname>:*\tGet status for all processes in a group\n"
		"status <name> <name>\tGet status for multiple named processes\n"
		"status\t\t\tGet all process status info\n"},
	{"stop", "stop <name>\t\tStop a process\n"
		"stop <gname>:*\t\tStop all processes in a group\n"
		"stop <name> <name>\tStop multiple processes or groups\n"
		"stop all\t\tStop all processes\n"},
	{"help", "help\t\tPrint a list of available actions\n"
		"help <action>\tPrint help for <action>\n"},
	{"daemon_exit", "Kill taskmaster daemon.\n"}, {NULL, ": no such command\n"}
};

void			d_help(char **av, int sock)
{
	int 	i;

	i = 0;
	if (!av[1])
		send_msg(sock,
				"=======================================================\n"
				"daemon_exit\texit\t\treload\t\trestart\n"
				"start\t\tstatus\t\tstop\n"
				"=======================================================\n");
	else
	{
		while (g_cmds[i].cmd && !ft_strequ(av[1], g_cmds[i].cmd))
			++i;
		if (!g_cmds[i].cmd)
			send_msg(sock, av[1]);
		send_msg(sock, g_cmds[i].desc);
	}
	send_msg(sock, NULL);
}
