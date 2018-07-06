/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 19:28:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/06 16:59:28 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DAEMON_H
# define	DAEMON_H

# include <libft.h>
# include <stdio.h>

# define RS_A 0
# define RS_N 1
# define RS_CRASH 2

typedef struct	s_dconf
{
	pid_t		dpid;
	uint16_t	port;
	uint8_t		ip[4];
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
