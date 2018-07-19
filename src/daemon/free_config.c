/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 16:10:34 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/19 09:57:48 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <daemon.h>

void		free_config_tree(void *content, size_t size)
{
	if (!content)
		return ;
	if (size == sizeof(t_yaml_tree))
	{
		ft_lstdel(&((t_yaml_tree *)content)->value, free_config_tree);
		free(((t_yaml_tree *)content)->key);
	}
	free(content);
}

void		free_config_proc(void *content, size_t size)
{
	(void)size;
	free(((t_proc *)content)->name);
	free(((t_proc *)content)->cmd);
	free(((t_proc *)content)->workingdir);
	free(((t_proc *)content)->stdout);
	free(((t_proc *)content)->stderr);
	free(((t_proc *)content)->stdin);
	free(((t_proc *)content)->jobs);
	ft_strarr_free(((t_proc *)content)->argv);
	ft_strarr_free(((t_proc *)content)->env);
	free(content);
}

void	free_config_daemon(t_dconf *conf)
{
	free(conf->out_log);
	free(conf->err_log);
	free(conf->ip);
	free(conf->config_file);
}