/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:43:03 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 10:35:44 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static t_list	*get_node_by_name(t_list *conf, char *name)
{
	while (conf)
	{
		if (ft_strequ(((t_proc *)conf->content)->name, name))
			return (conf);
		conf = conf->next;
	}
	return (NULL);
}

static void		add_new_proc(t_list *conf)
{
	t_list	*prev_node;
	t_list	*first_node;

	prev_node = NULL;
	first_node = conf;
	while (conf)
	{
		if (conf->content_size)
		{
			prev_node ? prev_node->next = conf->next :
										(first_node = conf->next);
			ft_lstadd_end(&get_dconf()->proc, conf);
			conf->next = NULL;
			proc_start(conf->content, -1, get_dconf()->sockfd);
			conf = prev_node ? prev_node->next : first_node;
			continue ;
		}
		prev_node = conf;
		conf = conf->next;
	}
	ft_lstdel(&first_node, free_config_proc);
}

static void		delete_old_proc(void)
{
	t_list	*prev_node;
	t_list	*conf;

	conf = get_dconf()->proc;
	prev_node = NULL;
	while (conf)
	{
		if (!conf->content_size)
		{
			prev_node ? prev_node->next = conf->next :
							(get_dconf()->proc = conf->next);
			ft_lstdelone(&conf, free_config_proc);
			conf = prev_node ? prev_node->next : get_dconf()->proc;
			continue ;
		}
		prev_node = conf;
		conf = conf->next;
	}
}

static void		cmp_conf(t_list *old_conf, t_list *new_conf, int sock)
{
	t_list	*proc;

	while (old_conf)
	{
		if ((proc = get_node_by_name(new_conf,
				((t_proc *)old_conf->content)->name)))
		{
			if (cmp_one_proc(old_conf->content, proc->content))
			{
				ft_printf("%s: reload\n", ((t_proc *)old_conf->content)->name);
				proc_stop(old_conf->content, -1, sock);
				swap_content(old_conf, proc);
				((t_proc*)(old_conf->content))->autostart ?
					proc_start(old_conf->content, -1, sock) : 0;
			}
			proc->content_size = 0;
		}
		else
			old_conf->content_size = 0;
		old_conf = old_conf->next;
	}
	delete_old_proc();
	add_new_proc(new_conf);
}

void			d_reload(char **av, int sock)
{
	t_list	*old_conf;
	t_dconf	new_conf;

	(void)av;
	ft_bzero(&new_conf, sizeof(t_dconf));
	old_conf = get_dconf()->proc;
	parse_config(&new_conf);
	cmp_conf(old_conf, new_conf.proc, sock);
	free_config_daemon(&new_conf);
	send_msg(sock, NULL);
}
