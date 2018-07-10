/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:37:05 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/07 16:06:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static void	outputs()
{
	t_list *tmp = get_dconf()->proc;

	while (tmp)
	{
		ft_printf("name: %s\n", ((t_proc *)(tmp->content))->name);
		if (((t_proc *)(tmp->content))->argv)
		{
			int i = -1;
			while (((t_proc *)(tmp->content))->argv[++i])
				ft_printf("argv[%i]: %s\n", i, ((t_proc *)(tmp->content))->argv[i]);
		}
		ft_printf("numproc: %i\n", ((t_proc *)(tmp->content))->numprocs);
		ft_printf("umask: %i\n", ((t_proc *)(tmp->content))->umask);
		ft_printf("workingdir: %s\n", ((t_proc *)(tmp->content))->workingdir);
		ft_printf("autostart: %i\n", ((t_proc *)(tmp->content))->autostart);
		ft_printf("autorestart: %i\n", ((t_proc *)(tmp->content))->autorestart);
		ft_printf("starttime: %i\n", ((t_proc *)(tmp->content))->starttime);
		ft_printf("startretries: %i\n", ((t_proc *)(tmp->content))->startretries);
		ft_printf("stdout: %s\n", ((t_proc *)(tmp->content))->stdout);
		ft_printf("stderr: %s\n", ((t_proc *)(tmp->content))->stderr);
		ft_printf("stopsignal: %i\n", ((t_proc *)(tmp->content))->stopsignal);
		for (int i = 0; i < 255; i++)
			if (((t_proc *)(tmp->content))->exitcodes[i])
				ft_printf("exitcode: %i\n", i);
		ft_printf("\n--------------\n\n");
		tmp = tmp->next;
	}
	ft_printf("logout: %s\n", get_dconf()->out_log);
	ft_printf("logerr: %s\n", get_dconf()->err_log);
	ft_printf("ip: %s\n", get_dconf()->ip);
	ft_printf("port: %i\n", get_dconf()->port);
}

static void	record_config_proc2(t_key_val *pair, t_proc *proc)
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
	if (ft_strequ(pair->key, "stderr"))
		proc->stderr = ft_strdup(pair->val);
	else if (ft_strequ(pair->key, "stopsignal"))
	{
		while (sig[++i].signame)
			if (ft_strequ(pair->val, sig[i].signame))
				proc->stopsignal = sig[i].sig;
	}
	else
		ft_printf("KEY: %s\nVALUE: %s\n", pair->key, pair->val);
}

static void	record_config_proc(t_key_val *pair, t_proc *proc)
{
		if (ft_strequ(pair->key, "cmd"))
			proc->argv = ft_strsplit(pair->val, ' ');
		else if (ft_strequ(pair->key, "numprocs"))
			proc->numprocs = ft_atoi(pair->val);
		else if (ft_strequ(pair->key, "umask"))
			proc->umask = ft_atol(pair->val);
		else if (ft_strequ(pair->key, "workingdir"))
			proc->workingdir = ft_strdup(pair->val);
		else if (ft_strequ(pair->key, "autostart"))
			proc->autostart = ft_strequ(pair->val, "true") ? 1 : 0;
		else if (ft_strequ(pair->key, "autorestart"))
			proc->autorestart = ft_strequ(pair->val, "expected") ? 1 : 0;
		else if (ft_strequ(pair->key, "exitcodes"))
			proc->exitcodes[ft_atoi(pair->val)] = true;
		else if (ft_strequ(pair->key, "startretries"))
			proc->startretries = ft_atol(pair->val);
		else if (ft_strequ(pair->key, "starttime"))
			proc->starttime = ft_atol(pair->val);
		else if (ft_strequ(pair->key, "stoptime"))
			proc->stoptime = ft_atol(pair->val);
		else if (ft_strequ(pair->key, "stdout"))
			proc->stdout = ft_strdup(pair->val);
		else
			record_config_proc2(pair, proc);
}

static void	read_one_proc(yaml_parser_t *parser, t_key_val *pair, char *name)
{
	yaml_token_t	token;
	t_proc			proc;

	ft_bzero(&proc, sizeof(t_proc));
	proc.name = ft_strdup(name);
	while (1)
	{
		if (yaml_parser_scan(parser, &token) == 0)
			ft_fatal(EXIT_FAILURE, exit, "Config file is not valid\n");
		if (token.type == YAML_BLOCK_SEQUENCE_START_TOKEN)
			++pair->blocks;
		else if (token.type == YAML_BLOCK_END_TOKEN)
			--pair->blocks;
		if (token.type == YAML_KEY_TOKEN)
			ft_strdel(&pair->key);
		else if (token.type == YAML_SCALAR_TOKEN)
			!pair->key ? pair->key = ft_strdup((char*)token.data.scalar.value) :
			(pair->val = (char*)token.data.scalar.value);
		else if (token.type == YAML_BLOCK_END_TOKEN && pair->blocks == 0)
			break ;
		if (pair->key && pair->val)
			record_config_proc(pair, &proc);
		yaml_token_delete(&token);
	}
	ft_strdel(&pair->key);
	ft_lstpush_back(&get_dconf()->proc, &proc, sizeof(t_proc));
}

static void read_processes(yaml_parser_t *parser)
{
	yaml_token_t	token;
	t_key_val		pair;

	ft_bzero(&pair, sizeof(t_key_val));
	while (1)
	{
		if (yaml_parser_scan(parser, &token) == 0)
			ft_fatal(EXIT_FAILURE, exit, "Config file is not valid\n");
		if (token.type == YAML_KEY_TOKEN)
			ft_strdel(&pair.key);
		else if (token.type == YAML_SCALAR_TOKEN)
		{
			pair.blocks = 1;
			read_one_proc(parser, &pair, (char *)token.data.scalar.value);
		}
		else if (token.type == YAML_BLOCK_END_TOKEN)
			break ;
		yaml_token_delete(&token);
	}
	yaml_token_delete(&token);
}

static void		record_config_daemon(t_key_val *pair)
{
	if (ft_strequ(pair->key, "logout"))
		get_dconf()->out_log = ft_strdup(pair->val);
	else if (ft_strequ(pair->key, "logerr"))
		get_dconf()->err_log = ft_strdup(pair->val);
	else if (ft_strequ(pair->key, "port"))
		get_dconf()->port = ft_atoi(pair->val);
	else if (ft_strequ(pair->key, "ip"))
		get_dconf()->ip = ft_strdup(pair->val);
}


static void		read_daemon_config(yaml_parser_t *parser)
{
	yaml_token_t	token;
	t_key_val		pair;

	ft_bzero(&pair, sizeof(t_key_val));
	while (1)
	{
		if (yaml_parser_scan(parser, &token) == 0)
			ft_fatal(EXIT_FAILURE, exit, "Config file is not valid\n");
		if (token.type == YAML_KEY_TOKEN)
			ft_strdel(&pair.key);
		else if (token.type == YAML_SCALAR_TOKEN && pair.key == NULL &&
				ft_strequ((char*)token.data.scalar.value, "programs"))
			read_processes(parser);
		else if (token.type == YAML_SCALAR_TOKEN)
			!pair.key ? pair.key = ft_strdup((char*)token.data.scalar.value) :
			(pair.val = (char*)token.data.scalar.value);
		else if (token.type == YAML_STREAM_END_TOKEN)
			break ;
		if (pair.key && pair.val)
			record_config_daemon(&pair);
		yaml_token_delete(&token);
	}
	yaml_token_delete(&token);
	ft_strdel(&pair.key);
}

void			parse_config(void)
{
	FILE			*fp;
	yaml_parser_t	parser;

	if (!get_dconf()->config_file && access("taskmasterd.conf", F_OK) == 0)
		get_dconf()->config_file = "taskmasterd.conf";
	if (get_dconf()->config_file == NULL)
		ft_fatal(EXIT_FAILURE, exit, "No config file specified\n");
	if ((fp = fopen(get_dconf()->config_file, "r")) == NULL)
		ft_fatal(EXIT_FAILURE, exit, "%s: %s\n", strerror(errno),
				 get_dconf()->config_file);
	get_dconf()->proc = NULL; //TODO: delete
	if(!yaml_parser_initialize(&parser))
		ft_fatal(EXIT_FAILURE, exit, "Failed to initialize parser\n");
	yaml_parser_set_input_file(&parser, fp);
	read_daemon_config(&parser);
	yaml_parser_delete(&parser);
	outputs();
//	system("leaks taskmasterd");
	fclose(fp);
}
