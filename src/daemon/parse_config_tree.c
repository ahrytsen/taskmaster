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

static void		read_sequence(yaml_parser_t *parser, t_list **values)
{
	yaml_event_t	event;

	while (1)
	{
		if (!yaml_parser_parse(parser, &event))
			ft_fatal(EXIT_FAILURE, exit, "Config is not valid\n");
		if (event.type == YAML_SCALAR_EVENT)
			ft_lstpush_back(values, (char *)event.data.scalar.value,
							event.data.scalar.length);
		else if (event.type == YAML_SEQUENCE_END_EVENT)
			break ;
		yaml_event_delete(&event);
	}
	yaml_event_delete(&event);
}

static void		read_val(yaml_parser_t *parser, t_yaml_tree *node)
{
	yaml_event_t	event;

	if (!yaml_parser_parse(parser, &event))
		ft_fatal(EXIT_FAILURE, exit, "Config is not valid\n");
	if (event.type == YAML_SCALAR_EVENT)
	{
		node->type = singular_val;
		ft_lstpush_back(&node->value, (char *)event.data.scalar.value,
						event.data.scalar.length);
	}
	else if (event.type == YAML_MAPPING_START_EVENT)
	{
		node->type = mapping_val;
		node->value = read_mapping(parser);
	}
	else if (event.type == YAML_SEQUENCE_START_EVENT)
	{
		node->type = sequence_val;
		read_sequence(parser, &node->value);
	}
	yaml_event_delete(&event);
}

t_list			*read_mapping(yaml_parser_t *parser)
{
	yaml_event_t	event;
	t_yaml_tree		node;
	t_list			*parse_lst;

	parse_lst = NULL;
	ft_bzero(&node, sizeof(t_yaml_tree));
	while (1)
	{
		if (!yaml_parser_parse(parser, &event))
			ft_fatal(EXIT_FAILURE, exit, "Config is not valid\n");
		if (event.type == YAML_SCALAR_EVENT)
		{
			node.key = ft_strdup((char *)event.data.scalar.value);
			read_val(parser, &node);
			ft_lstpush_back(&parse_lst, &node, sizeof(node));
			ft_bzero(&node, sizeof(t_yaml_tree));
		}
		if (event.type == YAML_MAPPING_END_EVENT)
			break ;
		yaml_event_delete(&event);
	}
	yaml_event_delete(&event);
	return (parse_lst);
}

static t_list	*read_config(FILE *fp)
{
	yaml_parser_t	parser;
	yaml_event_t	event;
	t_list			*parse_lst;

	parse_lst = NULL;
	if (!yaml_parser_initialize(&parser))
		ft_fatal(EXIT_FAILURE, exit, "Failed to initialize parser\n");
	yaml_parser_set_input_file(&parser, fp);
	while (1)
	{
		if (!yaml_parser_parse(&parser, &event))
			ft_fatal(EXIT_FAILURE, exit, "Config is not valid\n");
		if (event.type == YAML_MAPPING_START_EVENT)
			parse_lst = read_mapping(&parser);
		if (event.type == YAML_STREAM_END_EVENT)
			break ;
		yaml_event_delete(&event);
	}
	yaml_event_delete(&event);
	yaml_parser_delete(&parser);
	return (parse_lst);
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
//	system("leaks taskmasterd");
	fclose(fp);
}
