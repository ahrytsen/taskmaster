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

//static void		record_to_dconf(t_key_val *pair)
//{
//	ft_printf("key: %s\n value: %s\n", pair->key, pair->val);
//	if (ft_strequ(pair->key, "logout"))
//		get_dconf()->out_log = ft_strdup(pair->val);
//	else if (ft_strequ(pair->key, "logerr"))
//		get_dconf()->err_log = ft_strdup(pair->val);
//	ft_bzero(pair, sizeof(t_key_val));
//}

static void		read_loop(yaml_parser_t *parser)
{
	yaml_token_t	token;
	t_key_val		pair;

	ft_bzero(&pair, sizeof(t_key_val));
	while (1)
	{
		yaml_parser_scan(parser, &token);
		if (token.type == YAML_SCALAR_TOKEN)
			;
		if (token.type == YAML_STREAM_END_TOKEN)
			break ;
		yaml_token_delete(&token);
	}
}

static void		read_config(FILE *fp)
{
	yaml_parser_t	parser;

	if(!yaml_parser_initialize(&parser))
		ft_fatal(EXIT_FAILURE, exit, "Failed to initialize parser\n");
	yaml_parser_set_input_file(&parser, fp);
	read_loop(&parser);
	ft_printf("%s\n%s\n", get_dconf()->out_log, get_dconf()->err_log);
	yaml_parser_delete(&parser);
//	system("leaks taskmasterd");
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
