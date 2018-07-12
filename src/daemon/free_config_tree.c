/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 16:10:34 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/12 17:39:35 by yvyliehz         ###   ########.fr       */
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