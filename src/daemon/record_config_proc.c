/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_config_proc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:50:47 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/23 12:32:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	record_exitcodes(t_proc *proc, t_yaml_tree *node)
{
	t_list	*tmp;

	if (node->type != sequence_val)
		return ;
	tmp = node->value;
	ft_bzero(&proc->exitcodes, 256);
	while (tmp)
	{
		proc->exitcodes[(uint8_t)ft_atoi(tmp->content)] = true;
		tmp = tmp->next;
	}
}

static void	record_config_env(t_proc *proc, t_yaml_tree *node)
{
	t_list	*tmp;
	int		env_amt;

	proc->env = NULL;
	tmp = node->value;
	env_amt = 0;
	while (tmp)
	{
		if (((t_yaml_tree *)tmp->content)->type == singular_val)
			env_amt++;
		tmp = tmp->next;
	}
	tmp = node->value;
	if (env_amt == 0)
		return ;
	proc->env = ft_memalloc((env_amt + 1) * sizeof(char *));
	while (tmp)
	{
		if (((t_yaml_tree *)tmp->content)->type == singular_val)
			*proc->env++ = ft_strhalfextend(
					ft_strjoin(((t_yaml_tree *)tmp->content)->key, "="),
					(((t_yaml_tree *)tmp->content)->value)->content);
		tmp = tmp->next;
	}
	proc->env -= env_amt;
}

static void	record_config_signal(t_proc *proc, t_yaml_tree *node)
{
	int					i;
	static const t_sig	sig[] = {{"HUP", SIGHUP}, {"INT", SIGINT},
	{"QUIT", SIGQUIT}, {"ILL", SIGILL}, {"TRAP", SIGTRAP}, {"ABRT", SIGABRT},
	{"EMT", SIGEMT}, {"FPE", SIGFPE}, {"KILL", SIGKILL}, {"BUS", SIGBUS},
	{"SEGV", SIGSEGV}, {"SYS", SIGSYS}, {"PIPE", SIGPIPE}, {"ALRM", SIGALRM},
	{"TERM", SIGTERM}, {"URG", SIGURG}, {"STOP", SIGSTOP}, {"TSTP", SIGTSTP},
	{"CONT", SIGCONT}, {"CHLD", SIGCHLD}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU},
	{"IO", SIGIO}, {"XCPU", SIGXCPU}, {"XFSZ", SIGXFSZ}, {"VTALRM", SIGVTALRM},
	{"PROF", SIGPROF}, {"WINCH", SIGWINCH}, {"INFO", SIGINFO},
	{"USR1", SIGUSR1}, {"USR2", SIGUSR2}, {NULL, 0}};

	i = -1;
	while (sig[++i].signame)
		if (ft_strequ(node->value->content, sig[i].signame))
			proc->stopsignal = sig[i].sig;
}

static void	record_config_proc2(t_proc *proc, t_yaml_tree *node)
{
	if (ft_strequ(node->key, "exitcodes"))
		record_exitcodes(proc, node);
	if (ft_strequ(node->key, "starttime"))
		proc->starttime = labs(ft_atol(node->value->content));
	else if (ft_strequ(node->key, "stoptime"))
		proc->stoptime = ft_atol(node->value->content);
	else if (ft_strequ(node->key, "stderr"))
		record_string_value(node, &proc->stderr);
	else if (ft_strequ(node->key, "stdout"))
		record_string_value(node, &proc->stdout);
	else if (ft_strequ(node->key, "stdin"))
		record_string_value(node, &proc->stdin);
	else if (ft_strequ(node->key, "numprocs"))
		proc->numprocs = abs(ft_atoi(node->value->content));
	else if (ft_strequ(node->key, "umask"))
		proc->umask = abs(ft_atoi_base(node->value->content, 8));
	else if (ft_strequ(node->key, "env"))
		record_config_env(proc, node);
	else if (ft_strequ(node->key, "stopsignal"))
		record_config_signal(proc, node);
}

void		record_config_proc(t_proc *proc, t_yaml_tree *node)
{
	if (!node->value || !node->value->content)
		return ;
	if (ft_strequ(node->key, "cmd"))
	{
		ft_strarr_free(proc->argv);
		proc->argv = ft_strsplit(node->value->content, ' ');
		record_string_value(node, &proc->cmd);
	}
	else if (ft_strequ(node->key, "workingdir"))
		record_string_value(node, &proc->workingdir);
	else if (ft_strequ(node->key, "autostart"))
		proc->autostart = ft_strequ(node->value->content, "true") ? 1 : 0;
	else if (ft_strequ(node->key, "autorestart"))
	{
		if (ft_strequ(node->value->content, "true"))
			proc->autorestart = 2;
		else if (ft_strequ(node->value->content, "unexpected"))
			proc->autorestart = 1;
		else
			proc->autorestart = 0;
	}
	else if (ft_strequ(node->key, "startretries"))
		proc->startretries = labs(ft_atol(node->value->content));
	else
		record_config_proc2(proc, node);
}
