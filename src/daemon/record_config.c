/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 16:49:59 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/11 16:50:00 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

//static void	outputs()
//{
//	while (tmp)
//	{
//		ft_printf("name: %s\n", ((t_proc *)(tmp->content))->name);
//		if (((t_proc *)(tmp->content))->argv)
//		{
//			int i = -1;
//			while (((t_proc *)(tmp->content))->argv[++i])
//				ft_printf("argv[%i]: %s\n", i, ((t_proc *)(tmp->content))->argv[i]);
//		}
//		ft_printf("numproc: %i\n", ((t_proc *)(tmp->content))->numprocs);
//		ft_printf("umask: %i\n", ((t_proc *)(tmp->content))->umask);
//		ft_printf("workingdir: %s\n", ((t_proc *)(tmp->content))->workingdir);
//		ft_printf("autostart: %i\n", ((t_proc *)(tmp->content))->autostart);
//		ft_printf("autorestart: %i\n", ((t_proc *)(tmp->content))->autorestart);
//		ft_printf("starttime: %i\n", ((t_proc *)(tmp->content))->starttime);
//		ft_printf("startretries: %i\n", ((t_proc *)(tmp->content))->startretries);
//		ft_printf("stdout: %s\n", ((t_proc *)(tmp->content))->stdout);
//		ft_printf("stderr: %s\n", ((t_proc *)(tmp->content))->stderr);
//		ft_printf("stopsignal: %i\n", ((t_proc *)(tmp->content))->stopsignal);
//		for (int i = 0; i < 255; i++)
//			if (((t_proc *)(tmp->content))->exitcodes[i])
//				ft_printf("exitcode: %i\n", i);
//		ft_printf("\n--------------\n\n");
//		tmp = tmp->next;
//	}
//	ft_printf("logout: %s\n", get_dconf()->out_log);
//	ft_printf("logerr: %s\n", get_dconf()->err_log);
//	ft_printf("ip: %s\n", get_dconf()->ip);
//	ft_printf("port: %i\n", get_dconf()->port);
//}

static void		record_string_value(char *var, char *value)
{
	free(var);
	var = value;
	value = NULL;
}

//static void	record_config_proc2(t_key_val *pair, t_proc *proc)
//{
//	int					i;
//	static const t_sig	sig[] = {{"HUP", SIGHUP}, {"INT", SIGINT},
//	{"QUIT", SIGQUIT}, {"ILL", SIGILL}, {"TRAP", SIGTRAP}, {"ABRT", SIGABRT},
//	{"EMT", SIGEMT}, {"FPE", SIGFPE}, {"KILL", SIGKILL}, {"BUS", SIGBUS},
//	{"SEGV", SIGSEGV}, {"SYS", SIGSYS}, {"PIPE", SIGPIPE}, {"ALRM", SIGALRM},
//	{"TERM", SIGTERM}, {"URG", SIGURG}, {"STOP", SIGSTOP}, {"TSTP", SIGTSTP},
//	{"CONT", SIGCONT}, {"CHLD", SIGCHLD}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU},
//	{"IO", SIGIO}, {"XCPU", SIGXCPU}, {"XFSZ", SIGXFSZ}, {"VTALRM", SIGVTALRM},
//	{"PROF", SIGPROF}, {"WINCH", SIGWINCH}, {"INFO", SIGINFO},
//	{"USR1", SIGUSR1}, {"USR2", SIGUSR2}, {NULL, 0}};
//
//	i = -1;
//	if (ft_strequ(pair->key, "stderr"))
//		proc->stderr = ft_strdup(pair->value);
//	else if (ft_strequ(pair->key, "stopsignal"))
//	{
//		while (sig[++i].signame)
//			if (ft_strequ(pair->value, sig[i].signame))
//				proc->stopsignal = sig[i].sig;
//	}
//	else
//		ft_printf("KEY: %s\nVALUE: %s\n", pair->key, pair->value);
//}

//static void	record_config_proc(t_key_val *pair, t_proc *proc)
//{
//		if (ft_strequ(pair->key, "cmd"))
//			proc->argv = ft_strsplit(pair->value, ' ');
//		else if (ft_strequ(pair->key, "numprocs"))
//			proc->numprocs = ft_atoi(pair->value);
//		else if (ft_strequ(pair->key, "umask"))
//			proc->umask = ft_atol(pair->value);
//		else if (ft_strequ(pair->key, "workingdir"))
//			proc->workingdir = ft_strdup(pair->value);
//		else if (ft_strequ(pair->key, "autostart"))
//			proc->autostart = ft_strequ(pair->value, "true") ? 1 : 0;
//		else if (ft_strequ(pair->key, "autorestart"))
//			proc->autorestart = ft_strequ(pair->value, "expected") ? 1 : 0;
//		else if (ft_strequ(pair->key, "exitcodes"))
//			proc->exitcodes[ft_atoi(pair->value)] = true;
//		else if (ft_strequ(pair->key, "startretries"))
//			proc->startretries = ft_atol(pair->value);
//		else if (ft_strequ(pair->key, "starttime"))
//			proc->starttime = ft_atol(pair->value);
//		else if (ft_strequ(pair->key, "stoptime"))
//			proc->stoptime = ft_atol(pair->value);
//		else if (ft_strequ(pair->key, "stdout"))
//			proc->stdout = ft_strdup(pair->value);
//		else
//			record_config_proc2(pair, proc);
//}
//

static void		record_config_daemon(t_list	*lst)
{
	t_yaml_tree	*tmp;

	tmp = lst->content;
	if (tmp->type != singular_val)
		return ;
	if (ft_strequ(tmp->key, "logout"))
		get_dconf()->out_log = tmp->value->content;
	else if (ft_strequ(tmp->key, "logerr"))
		get_dconf()->err_log = tmp->value->content;
	else if (ft_strequ(tmp->key, "port"))
	{
		get_dconf()->port = ft_atoi(tmp->value->content);
		free(tmp->value->content);
	}
	else if (ft_strequ(tmp->key, "ip"))
		get_dconf()->ip = tmp->value->content;
	tmp->value->content = NULL;
}

static t_proc	*find_proc(char *proc_name)
{
	t_list	*tmp;

	tmp = get_dconf()->proc;
	while (tmp)
	{
		if (ft_strequ(((t_proc *)tmp->content)->name, proc_name))
			return (tmp->content);
		tmp = tmp->next;
	}
	ft_lstpush_back()
	return ()
}

static void		record_one_proc(t_list *proc)
{
	t_list	*proc;
//	while ()
}

void			record_config(t_list *parse_lst)
{
	while (parse_lst)
	{
//		if (((t_yaml_tree *)parse_lst->content)->type == mapping_val)
//			;
		if (!ft_strequ(((t_yaml_tree *)parse_lst->content)->key, "programs"))
			record_config_daemon(parse_lst);
		else
			record_one_proc(((t_yaml_tree *)parse_lst->content)->value);
		parse_lst = parse_lst->next;
	}
}