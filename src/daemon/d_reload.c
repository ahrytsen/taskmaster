/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:43:03 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/18 16:59:11 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

//static void	swap_var(void **old_var,  void **new_var)
//{
//	void	*tmp;
//
//	tmp = *old_var;
//	*old_var = *new_var;
//	*new_var = tmp;
//}

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

//static void		swap_conf_vars(t_proc *old_conf, t_proc *new_conf)
//{
//	if (!cmp_strings(old_conf->cmd, new_conf->cmd))
//		swap_var((void **)&old_conf->cmd, (void **)&new_conf->cmd);
//	if (!cmp_strings(old_conf->workingdir, new_conf->workingdir))
//		swap_var((void **)&old_conf->workingdir,
//				 (void **)&new_conf->workingdir);
//	if (!cmp_strings(old_conf->stdout, new_conf->stdout))
//		swap_var((void **)&old_conf->stdout, (void **)&new_conf->stdout);
//	if (!cmp_strings(old_conf->stderr, new_conf->stderr))
//		swap_var((void **)&old_conf->stderr, (void **)&new_conf->stderr);
//	if (!cmp_strings(old_conf->stdin, new_conf->stdin))
//		swap_var((void **)&old_conf->stdin, (void **)&new_conf->stdin);
//	if (old_conf->numprocs != new_conf->numprocs)
//		swap_var((void **)&old_conf->numprocs,
//				 (void **)&new_conf->numprocs);
//	if (old_conf->umask != new_conf->umask)
//		swap_var((void **)&old_conf->umask, (void **)&new_conf->umask);
//	while (old_conf->env && *old_conf->env)
//		if (!new_conf->env || !ft_strequ(*old_conf->env++, *new_conf->env++))
//			swap_var((void **)&old_conf->env, (void **)&new_conf->env);
//}

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
			ft_lstadd(&get_dconf()->proc, conf);
			proc_start(conf->content, -1, get_dconf()->sockfd);
			prev_node ? prev_node->next = conf->next :
									(first_node = conf->next);
			conf->next = NULL;
			conf = prev_node ? prev_node->next : first_node;
			continue ;
		}
		prev_node = conf;
		conf = conf->next;
	}
	while (first_node)
	{
		ft_printf("%s\n", ((t_proc *)first_node->content)->name);
		first_node = first_node->next;
	}
//	ft_lstdel(&first_node, free_config_proc);
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

static void		cmp_conf(t_list *old_conf, t_list *new_conf)
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
				proc_stop(old_conf->content, -1, get_dconf()->sockfd);
				swap_content(old_conf, proc);
				proc_start(old_conf->content, -1, get_dconf()->sockfd);
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
	ft_printf("'d_reload' called\n");
	old_conf = get_dconf()->proc;
	parse_config(&new_conf);
	cmp_conf(old_conf, new_conf.proc);
//	ft_prociter(old_conf, sock, proc_stop);
//	ft_lstdel(&old_conf, free_config_proc);
	send_msg(sock, NULL);
}
