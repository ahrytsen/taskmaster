/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daemon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 19:15:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/20 17:03:14 by yvyliehz         ###   ########.fr       */
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

# define F_C 0b1
# define F_N 0b10

typedef struct	s_dconf
{
	char				*config_file;
	char				*out_log;
	char				*err_log;
	char 				*email;
	int					flags;
	pid_t				pid;
	uint16_t			port;
	char				*ip;
	int					sockfd;
	struct sockaddr_in	addr;
	int					err_fd;
	int					out_fd;
	t_list				*proc;
	pthread_t			serv_thread;
	pthread_mutex_t		dmutex;
	int					max_namelen;
}				t_dconf;

typedef struct	s_job
{
	int				p_in[2];
	int				p_out[2];
	int				p_err[2];
	enum			e_status
	{
		stop = 0,
		stoping,
		start,
		run,
		done,
		crash,
		fail,
		fatal
	}				status;
	int				ex_st;
	pid_t			pid;
	time_t			t;
	pthread_t		serv_thread;
	int				start_tries;
	pthread_mutex_t jmutex;
	int				service_pipe[2];
	char			*error;
	struct s_proc	*proc;
}				t_job;

typedef struct	s_proc
{
	char				*cmd;
	char				*name;
	char				**argv;
	t_job				*jobs;
	uint16_t			numprocs;
	mode_t				umask;
	char				*workingdir;
	uint8_t				autostart;
	enum				e_autorestart
	{
		never,
		always,
		unexp
	}					autorestart;
	char				exitcodes[256];
	time_t				starttime;
	int					startretries;
	int					stopsignal;
	time_t				stoptime;
	char				*stdout;
	char				*stderr;
	char				*stdin;
	char				**env;
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

typedef struct	s_help
{
	char 		*cmd;
	char 		*desc;
}				t_help;

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
int				proc_start_prnt(t_job *job);
void			proc_start_chld(t_job *job);
void			ft_prociter(t_list *lst, int sock,
							void (*f)(t_proc*, int, int));
void			proc_action_byname(t_list *lst, char *name, int sock,
									void (*action)(t_proc*, int, int));
/*
**				service_routines.c
*/
void			*proc_service(void *data);
/*
**				../exchange.c
*/
void			send_msg(int sock, char *msg);
ssize_t			receive_msg(char **line, int sock);
/*
**				d_status.c
*/
void			d_status(char **av, int sock);
/*
**				d_start.c
*/
void			d_start(char **av, int sock);
void			proc_start(t_proc *proc, int id, int sock);
/*
**				d_stop.c
*/
void			d_stop(char **av, int sock);
void			proc_stop(t_proc *proc, int id, int sock);
/*
**				d_reload.c
*/
void			d_reload(char **av, int sock);
/*
**				d_help.c
*/
void			d_help(char **av, int sock);
/*
**				d_restart.c
*/
void			d_restart(char **av, int sock);
/*
**				commands.c
*/
void			d_exit(char **av, int sock);
void			d_err_cmd(char **av, int sock);
/*
**				parse_config.c
*/
void			parse_config(t_dconf *conf);
t_list			*read_mapping(yaml_parser_t *parser);
/*
**				record_config.c
*/
void			record_config(t_list *parse_lst, t_dconf *conf);
void			record_string_value(t_yaml_tree *node, char **var);
/*
**				record_config_proc.c
*/
void			record_config_proc(t_proc *proc, t_yaml_tree *node);
/*
**				check_config.c
*/
int				check_config(t_dconf *conf);
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
void			free_config_daemon(t_dconf *conf);
/*
**				signals.c
*/
void			handle_signals(void);
/*
**				count_max_proclen.c
*/
int				count_max_proclen(t_list *proc);
/*
**				d_reload_funcs.c
*/
int				cmp_one_proc(t_proc *old_conf, t_proc *new_conf);
void			swap_content(t_list *node1, t_list *node2);
void			run_autostart(t_proc *proc, int id, int sock);

#endif
