/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:43:03 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/19 20:11:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int cmp_strings(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (1);
	return (ft_strequ(s1, s2));
}

static int cmd_proc_env(char **env_old, char **env_new)
{
	if (env_old)
		while (*env_old)
			if (!env_new || !ft_strequ(*env_old++, *env_new++))
				return (1);
	return (env_new && *env_new ? 1 : 0);
}

static int	cmp_one_proc(t_proc *old_conf, t_proc *new_conf)
{
	if (!cmp_strings(old_conf->cmd, new_conf->cmd) ||
			!cmp_strings(old_conf->workingdir, new_conf->workingdir) ||
			!cmp_strings(old_conf->stdout, new_conf->stdout) ||
			!cmp_strings(old_conf->stderr, new_conf->stderr) ||
			!cmp_strings(old_conf->stdin, new_conf->stdin) ||
			old_conf->numprocs != new_conf->numprocs ||
			old_conf->umask != new_conf->umask)
		return (1);
	return (cmd_proc_env(old_conf->env, new_conf->env));
}

static void		swap_content(t_list *node1, t_list *node2)
{
	void	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

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

void		d_reload(char **av, int sock)
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
//	system("leaks taskmasterd");
}
