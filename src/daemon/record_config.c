/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 16:49:59 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/18 12:47:51 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void			record_string_value(t_yaml_tree *node, char **var)
{
	if (node->type != singular_val || !node->value->content)
		return ;
	free(*var);
	*var = node->value->content;
	node->value->content = NULL;
}

static void		record_config_daemon(t_list *lst, t_dconf *conf)
{
	t_yaml_tree	*tmp;

	tmp = lst->content;
	if (tmp->type != singular_val || !tmp->value->content)
		return ;
	if (ft_strequ(tmp->key, "logout"))
		record_string_value(tmp, &conf->out_log);
	else if (ft_strequ(tmp->key, "logerr"))
		record_string_value(tmp, &conf->err_log);
	else if (ft_strequ(tmp->key, "port"))
		conf->port = ft_atoi(tmp->value->content);
	else if (ft_strequ(tmp->key, "ip"))
		record_string_value(tmp, &conf->ip);
}

static t_proc	*find_proc(char *proc_name, t_dconf *conf)
{
	t_proc	proc;
	t_proc	*procp;

	ft_bzero(&proc, sizeof(t_proc));
	procp = get_proc_byname(conf->proc, proc_name, NULL);
	if (procp == NULL)
		procp = ft_lstpush_back(&conf->proc, &proc, sizeof(t_proc))->content;
	return (procp);
}

static void		record_one_proc(t_list *procs, t_dconf *conf)
{
	t_proc	*proc;
	t_list	*node;

	while (procs)
	{
		proc = find_proc(((t_yaml_tree *) procs->content)->key, conf);
		if (proc->name == NULL)
		{
			proc->name = ((t_yaml_tree *)procs->content)->key;
			((t_yaml_tree *)procs->content)->key = NULL;
		}
		node = ((t_yaml_tree *)procs->content)->value;
		while (node)
		{
			record_config_proc(proc, node->content);
			node = node->next;
		}
		procs = procs->next;
	}
}

void			record_config(t_list *parse_lst, t_dconf *conf)
{
	t_list	*tmp;

	tmp = parse_lst;
	while (tmp)
	{
		if (!ft_strequ(((t_yaml_tree *)tmp->content)->key, "programs"))
			record_config_daemon(tmp, conf);
		else
			record_one_proc(((t_yaml_tree *)tmp->content)->value, conf);
		tmp = tmp->next;
	}
	ft_lstdel(&parse_lst, free_config_tree);
}
