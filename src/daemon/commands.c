/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 17:38:24 by ahrytsen          #+#    #+#             */

/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void	d_status(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_status' called on server side\n";
	ft_dprintf(1, "'d_status' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}

void	d_start(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_start' called on server side\n";
	ft_dprintf(1, "'d_start' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}

void	d_stop(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_stop' called on server side\n";
	ft_dprintf(1, "'d_stop' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}

void	d_restart(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_restart' called on server side\n";
	ft_dprintf(1, "'d_restert' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}

void	d_reread(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_reread' called on server side\n";
	ft_dprintf(1, "'d_reread' called\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}

void	d_exit(char **av, int sock)
{
	size_t	size;
	char	*msg;

	(void)av;
	msg = "'d_exit' called on server side: daemon will be stoped\n";
	ft_dprintf(1, "'d_exit' called: daemon will be stoped\n");
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
	exit(0);
}

void	d_err_cmd(char **av, int sock)
{
	size_t	size;
	char	*msg;

	msg = "error: command not found: ";
	ft_dprintf(2, "error: command not found: %s\n", *av);
	size = ft_strlen(msg) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, msg, size, 0);
	size = ft_strlen(*av) + 1;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, *av, size, 0);
	size = 2;
	send(sock, &size, sizeof(size_t), 0);
	send(sock, "\n", size, 0);
	size = 0;
	send(sock, &size, sizeof(size_t), 0);
}