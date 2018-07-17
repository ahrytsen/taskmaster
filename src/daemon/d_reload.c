/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:43:03 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/17 17:46:35 by yvyliehz         ###   ########.fr       */
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
			ft_strncmp(old_conf->exitcodes, new_conf->exitcodes, 255) ||
			old_conf->numprocs != new_conf->numprocs ||
			old_conf->umask != new_conf->umask ||
			old_conf->autostart != new_conf->autostart ||
			old_conf->autorestart != new_conf->autorestart ||
			old_conf->starttime != new_conf->starttime ||
			old_conf->startretries != new_conf->startretries ||
			old_conf->stopsignal != new_conf->stopsignal ||
			old_conf->stoptime != new_conf->stoptime)
		return (1);
	return (cmd_proc_env(old_conf->env, new_conf->env));
}

static void	cmp_conf(t_list **old_conf, t_list *new_conf)
{
	t_list	*tmp1;
	void	*tmp2;
	t_list	*tmp3;

	tmp1 = *old_conf;
	tmp3 = NULL;
	while (tmp1)
	{
		if ((tmp2 = get_proc_byname(new_conf,
						((t_proc *)tmp1->content)->name, NULL)))
		{
			if (cmp_one_proc(tmp1->content, tmp2))
			{
				ft_printf("ASD\n");
				proc_stop(tmp1->content, -1, get_dconf()->sockfd);
				proc_start(new_conf->content, -1, get_dconf()->sockfd);
			}
			tmp2 = tmp1->next;
			if (tmp3)
				tmp3->next = tmp1->next;
			else
				*old_conf = tmp1->next;
//			ft_lstdelone(&tmp1, free_config_proc);
			tmp1 = tmp2;
			continue ;
		}
		tmp3 = tmp1;
		tmp1 = tmp1->next;
	}
	ft_printf("---------------------\n");
	tmp1 = *old_conf;
	while (tmp1)
	{
		ft_printf("PROC: %s\n",((t_proc *)tmp1->content)->name);
		tmp1 = tmp1->next;
	}
}

void		d_reload(char **av, int sock)
{
	t_list	*old_conf;

	(void)av;
	ft_printf("'d_reload' called\n");
	old_conf = get_dconf()->proc;
	get_dconf()->proc = NULL;
	parse_config();
	cmp_conf(&old_conf, get_dconf()->proc);
	ft_prociter(old_conf, sock, proc_stop);
	ft_lstdel(&old_conf, free_config_proc);
	send_msg(sock, NULL);
}
