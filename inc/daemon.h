/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 19:28:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 18:18:34 by ahrytsen         ###   ########.fr       */
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

typedef struct	s_dconf
{
	char				*config_file;
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
	uint16_t	numproc;
	uint8_t 	autostart;
	uint8_t		autorestart;
	int 		expected_status;
	time_t		lt_success;
	int 		rs_efforts;
	int 		gf_stop_sig;
	time_t 		t_after_gf_s;
	char 		*log_out;
	char 		*log_err;
	char 		**env;
	char 		*cwd;
	mode_t 		umask;
}				t_proc;

#endif
