/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:37:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 15:48:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

static int	ft_getcurx(void)
{
	char	buf[21];
	char	*st;

	ft_bzero(buf, sizeof(buf));
	ft_dprintf(0, "\033[6n");
	if (read(0, buf, 20) == -1)
		return (-1);
	if ((st = ft_strchr(buf, ';')))
		return (ft_atoi(++st));
	return (0);
}

void		ft_prompt(void)
{
	int		tmp;

	tmp = 0;
	if (isatty(2))
	{
		if (ft_getcurx() != 1)
			ft_dprintf(2, "%s%%%s\n", get_term()->iv_on, get_term()->iv_off);
		tmp = ft_dprintf(2, "taskmaster> ");
	}
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
}
