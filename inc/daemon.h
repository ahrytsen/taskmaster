/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 18:22:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/12 15:12:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAEMON_H
# define DAEMON_H

# include <libft.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <yaml.h>
# include <stdbool.h>

# define RS_A 0
# define RS_N 1
# define RS_CRASH 2

# define F_C 0b1
# define F_N 0b10

# define ST_RUN 0b1
# define ST_DONE 0b10
# define ST_CRASH 0b100
# define ST_STOP 0b1000

# define GET_VAR(Variable) (#Variable)

typedef struct	s_dconf
{
	char				*config_file;
	char				*out_log;
	char				*err_log;
	int					flags;
	pid_t				pid;
	uint16_t			port;
	char				*ip;
	int					sockfd;
	struct sockaddr_in	addr;
	int					err_fd;
	int					out_fd;
	t_list				*proc;
}				t_dconf;

typedef struct	s_job
{
	int		status;
	int		std_in;
	int		std_out;
	int		std_err;
	int		ex_st;
	pid_t	pid;
	time_t	t;
}				t_job;

typedef struct	s_proc
{
	char 			*name;
	char			**argv;
	t_job			*jobs;
	uint16_t		numprocs;
	mode_t 			umask;
	char 			*workingdir;
	uint8_t 		autostart;
	uint8_t			autorestart;
	char 			exitcodes[255];
	time_t			starttime;
	int 			startretries;
	int 			stopsignal;
	time_t 			stoptime;
	char 			*stdout;
	char 			*stderr;
	char 			**env;
}				t_proc;

typedef struct	s_dispatcher
{
	char	*cmd;
	void	(*exec)(char**, int);
}				t_disp;

typedef struct	s_sig
{
	char	*signame;
	int		sig;
}				t_sig;

typedef struct	s_key_val
{
	char	*key;
	char 	*val;
	int 	blocks;
//	t_proc	*proc;
}				t_key_val;

/*
**				d_flags.c
*/
void			d_usage(char *av);
void			check_flags(int ac, char **av);
/*
**				d_init.c
*/
t_dconf			*get_dconf(void);
void			demonaize(void);
void			d_init(void);
/*
**				proc_utils.c
*/
t_proc			*get_proc_byname(t_list *proc, char *name, int *id);
void			proc_start_chld(t_proc *proc);
void			ft_prociter(t_list *lst, int sock,
							void (*f)(t_proc*, int, int));
/*
**				exchange.c
*/
void			send_msg(int sock, char	*msg);
/*
**				d_status.c
*/
void			d_status(char **av, int sock);
/*
**				commands.c
*/
void			d_start(char **av, int sock);
void			d_stop(char **av, int sock);
void			d_restart(char **av, int sock);
void			d_reread(char **av, int sock);
void			d_exit(char **av, int sock);
void			d_err_cmd(char **av, int sock);
/*
**				parse_config.c
*/
void			parse_config(void);

#endif
