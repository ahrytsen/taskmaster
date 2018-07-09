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
#include <assert.h>
#include <yaml.h>

static void	outputs()
{
	if (get_dconf()->proc)
	{
		ft_printf("name: %s\n", get_dconf()->proc->name);
		if (get_dconf()->proc->argv)
		{
			int i = -1;
			while (get_dconf()->proc->argv[++i])
				ft_printf("argv[%i]: %s\n", i, get_dconf()->proc->argv[i]);
		}
		ft_printf("numproc: %i\n", get_dconf()->proc->numprocs);
		ft_printf("umask: %i\n", get_dconf()->proc->umask);
		ft_printf("workingdir: %s\n", get_dconf()->proc->workingdir);
		ft_printf("autostart: %i\n", get_dconf()->proc->autostart);
		ft_printf("autorestart: %i\n", get_dconf()->proc->autorestart);
		ft_printf("starttime: %i\n", get_dconf()->proc->starttime);
		ft_printf("startretries: %i\n", get_dconf()->proc->startretries);
		ft_printf("stdout: %s\n", get_dconf()->proc->stdout);
		ft_printf("stderr: %s\n", get_dconf()->proc->stderr);
		for (int i = 0; i < 255; i++)
			if (get_dconf()->proc->exitcodes[i])
				ft_printf("exitcode: %i\n", i);
		ft_printf("\n--------------\n\n");
	}
	ft_printf("logout: %s\n", get_dconf()->out_log);
	ft_printf("logerr: %s\n", get_dconf()->err_log);
	ft_printf("ip: %s\n", get_dconf()->ip);
	ft_printf("port: %i\n", get_dconf()->port);
}

//static void	record_config_proc(t_key_val *pair)
//{
//		if (ft_strequ(pair->key, "cmd"))
//			pair->proc->argv = ft_strsplit(pair->val, ' ');
//		else if (ft_strequ(pair->key, "numprocs"))
//			pair->proc->numprocs = ft_atoi(pair->val);
//		else if (ft_strequ(pair->key, "umask"))
//			pair->proc->umask = ft_atoi(pair->val);
//		else if (ft_strequ(pair->key, "workingdir"))
//			pair->proc->workingdir = ft_strdup(pair->val);
//		else if (ft_strequ(pair->key, "autostart"))
//			pair->proc->umask = ft_atoi(pair->val);
//		else if (ft_strequ(pair->key, "autorestart"))
//			pair->proc->umask = ft_atoi(pair->val);
//		else if (ft_strequ(pair->key, "exitcodes"))
//			pair->proc->exitcodes[ft_atoi(pair->val)] = true;
//		else if (ft_strequ(pair->key, "umask"))
//			pair->proc->umask = ft_atoi(pair->val);
//	ft_strdel(&pair->key);
//	ft_strdel(&pair->val);
//}

//static void		get_key_value(yaml_parser_t *parser, yaml_token_t *token, t_key_val	*pair)
//{
//	assert(yaml_parser_scan(*parser, token));
//}
//
//static void 	read_proc_loop(yaml_parser_t *parser)
//{
//	yaml_token_t	token;
//	t_key_val		pair;
//
//	ft_bzero(&pair, sizeof(t_key_val));
//	get_dconf()->proc = ft_memalloc(sizeof(t_proc));
//	pair.proc = get_dconf()->proc;
//	pair.blocks = 0;
//	while (1)
//	{
//		if (yaml_parser_scan(parser, &token) == 0)
//			ft_fatal(EXIT_FAILURE, exit, "Config file is not valid\n");
//		if (token.type == YAML_BLOCK_SEQUENCE_START_TOKEN ||
//				token.type == YAML_BLOCK_MAPPING_START_TOKEN)
//			++pair.blocks;
//		if (token.type == YAML_BLOCK_END_TOKEN)
//			--pair.blocks;
//		if (pair.blocks == 0 && ft_printf("ASD\n"))
//			break ;
//		if (token.type == YAML_KEY_TOKEN)
//			ft_strdel(&pair.key);
//		if (token.type == YAML_SCALAR_TOKEN)
//		{
//			if (pair.proc->name == NULL)
//				pair.proc->name = ft_strdup((char *)token.data.scalar.value);
//			else if (pair.key == NULL)
//				pair.key = ft_strdup((char *)token.data.scalar.value);
//			else
//				pair.val = ft_strdup((char *)token.data.scalar.value);
//		}
//		if (pair.key && pair.val)
//			record_config(&pair);
//		if (token.type == YAML_STREAM_END_TOKEN)
//			break ;
//		yaml_token_delete(&token);
//	}
//	yaml_token_delete(&token);
//}

static void		read_proc_config(yaml_parser_t *parser)
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
			pair.key == NULL ?
					pair.key = ft_strdup((char*)token.data.scalar.value) :
			(pair.val = ft_strdup((char*)token.data.scalar.value));
		else if (token.type == YAML_STREAM_END_TOKEN)
			break ;
//		if (pair.key && pair.val)
//			record_config_proc(&pair);
		yaml_token_delete(&token);
	}
	yaml_token_delete(&token);
	ft_strdel(&pair.key);
	ft_strdel(&pair.val);
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
	ft_strdel(&pair->val);
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
		else if (token.type == YAML_SCALAR_TOKEN)
			pair.key == NULL ?
			pair.key = ft_strdup((char*)token.data.scalar.value) :
			(pair.val = ft_strdup((char*)token.data.scalar.value));
		else if (token.type == YAML_STREAM_END_TOKEN)
			break ;
		if (pair.key && pair.val)
			record_config_daemon(&pair);
		yaml_token_delete(&token);
	}
	yaml_token_delete(&token);
	ft_strdel(&pair.key);
	ft_strdel(&pair.val);
}

static void		read_config(FILE *fp)
{
	yaml_parser_t	parser;

	if(!yaml_parser_initialize(&parser))
		ft_fatal(EXIT_FAILURE, exit, "Failed to initialize parser\n");
	yaml_parser_set_input_file(&parser, fp);
	read_daemon_config(&parser);
	read_proc_config(&parser);
//	ft_printf("%s\n%s\n", get_dconf()->out_log, get_dconf()->err_log);
	yaml_parser_delete(&parser);
	outputs();
	system("leaks taskmasterd");
}

void			parse_config(void)
{
	FILE			*fp;

	if (!get_dconf()->config_file && access("taskmasterd.conf", F_OK) == 0)
		get_dconf()->config_file = "taskmasterd.conf";
	if (get_dconf()->config_file == NULL)
		ft_fatal(EXIT_FAILURE, exit, "No config file specified\n");
	if ((fp = fopen(get_dconf()->config_file, "r")) == NULL)
		ft_fatal(EXIT_FAILURE, exit, "%s: %s\n", strerror(errno),
				 get_dconf()->config_file);
	read_config(fp);
	fclose(fp);
}
