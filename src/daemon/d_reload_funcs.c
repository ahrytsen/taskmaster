/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_reload_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 10:32:40 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 10:35:44 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

static int	cmp_strings(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (1);
	return (ft_strequ(s1, s2));
}

static int	cmd_proc_env(char **env_old, char **env_new)
{
	if (env_old)
		while (*env_old)
			if (!env_new || !ft_strequ(*env_old++, *env_new++))
				return (1);
	return (env_new && *env_new ? 1 : 0);
}

int			cmp_one_proc(t_proc *old_conf, t_proc *new_conf)
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

void		swap_content(t_list *node1, t_list *node2)
{
	void	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}
