/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 19:15:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/15 18:05:27 by yvyliehz         ###   ########.fr       */
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
# include <time.h>
# include <signal.h>
# include <arpa/inet.h>
# include <pthread.h>

//# define RS_A 0
//# define RS_N 1
//# define RS_CRASH 2

# define F_C 0b1
# define F_N 0b10

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
	pthread_t 			serv_thread;
	pthread_mutex_t 	dmutex;
}				t_dconf;

typedef struct	s_job
{
	enum			e_status
	{
		stop = 0,
		start,
		run,
		done,
		crash,
		fail,
		fatal
	}				status;
	int				std_in;
	int				std_out;
	int				std_err;
	int				ex_st;
	pid_t			pid;
	time_t			t;
	pthread_t 		serv_thread;
	int 			startretries;
	pthread_mutex_t jmutex;
	struct s_proc	*proc;
}				t_job;

typedef struct	s_proc
{
	char 				*cmd;
	char 				*name;
	char				**argv;
	t_job				*jobs;
	uint16_t			numprocs;
	mode_t 				umask;
	char 				*workingdir;
	uint8_t 			autostart;
	uint8_t				autorestart;
	char 				exitcodes[255];
	time_t				starttime;
	int 				startretries;
	int 				stopsignal;
	time_t 				stoptime;
	char 				*stdout;
	char 				*stderr;
	char 				*stdin;
	char				**env;
	pthread_mutex_t 	pmutex;
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

typedef struct	s_yaml_tree
{
	char	*key;
	t_list	*value;
	enum	e_type
	{
		singular_val,
		sequence_val,
		mapping_val
	}		type;
}				t_yaml_tree;

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
void			proc_action_byname(t_list *lst, char *name, int sock,
									void (*action)(t_proc*, int, int));
void			*wait_routine(void *data);
/*
**				../exchange.c
*/
void			send_msg(int sock, char	*msg);
ssize_t			recive_msg(char **line, int sock);
/*
**				d_status.c
*/
void			d_status(char **av, int sock);
/*
**				d_start.c
*/
void			d_start(char **av, int sock);
/*
**				d_stop.c
*/
void			d_stop(char **av, int sock);
void			proc_stop(t_proc *proc, int id, int sock);
/*
**				commands.c
*/
void			d_restart(char **av, int sock);
void			d_reread(char **av, int sock);
void			d_exit(char **av, int sock);
void			d_err_cmd(char **av, int sock);
/*
**				parse_config.c
*/
void			parse_config(void);
t_list			*read_mapping(yaml_parser_t *parser);
/*
**				record_config.c
*/
void			record_config(t_list *parse_lst);
void			record_string_value(t_yaml_tree *node, char **var);
/*
**				record_config_proc.c
*/
void			record_config_proc(t_proc *proc, t_yaml_tree *node);
/*
**				check_config.c
*/
int				check_config(void);
/*
**				debug.c										TODO:delete
*/
void			output_parse_tree(t_list *parse_lst);
void			outputs();
/*
**				free_config.c
*/
void			free_config_tree(void *content, size_t size);
void			free_config_proc(void *content, size_t size);
void			free_config_daemon(void);
/*
**				d_reload.c
*/
void			d_reload(char **av, int sock);
#endif
