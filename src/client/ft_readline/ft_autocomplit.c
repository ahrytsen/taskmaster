/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:19:38 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 17:41:29 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

static char	*ft_search_builtin(char *line)
{
	int					i;
	int					len;
	const static char	*builtins[] = {"start", "status", "stop", "restart",
										"exit", "reload", "d_exit", "help",
										NULL};

	i = 0;
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (builtins[i] && ft_strncmp(line, builtins[i], len))
		i++;
	return (builtins[i] ? ft_strdup(builtins[i]) : NULL);
}

void		ft_autocomplit(t_line *cursor)
{
	char	*line;
	char	*res;
	char	*tmp;

	res = NULL;
	line = NULL;
	if ((line = line_tostr(&cursor, 0))
		&& (res = ft_search_builtin(line)))
	{
		tmp = res + ft_strlen(line);
		while (*tmp && ft_printf("%c", *tmp))
			line_add(cursor, *tmp++);
		ft_printf(" ");
		line_add(cursor, ' ');
	}
	else
		ft_printf("\a");
	free(res);
	free(line);
}
