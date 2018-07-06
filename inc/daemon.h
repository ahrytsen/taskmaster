/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 18:22:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 20:43:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DAEMON_H
# define	DAEMON_H

# include <libft.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# define RS_A 0
# define RS_N 1
# define RS_CRASH 2

# define F_C 0b1
# define F_N 0b10
# define F_H 0b100

typedef struct	s_dconf
{
	char				*config_file;
	int					flags;
	pid_t				dpid;
	uint16_t			port;
	uint8_t				ip[4];
	int					sock_id;
	struct sockaddr_in	addr;
	int					err_fd;
	int					out_fd;
}				t_dconf;

typedef struct	s_proc
{
	char		**argv;
	uint16_t	numprocs;
	mode_t 		umask;
	char 		*workingdir;
	uint8_t 	autostart;
	uint8_t		autorestart;
	int 		exitcodes;
	time_t		starttime;
	int 		startretries;
	int 		stopsignal;
	time_t 		stoptime;
	char 		*stdout;
	char 		*stderr;
	char 		**env;
}				t_proc;

#endif
