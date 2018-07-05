/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:20:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 15:34:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int		ft_del(uint64_t buf)
{
	if (!get_term()->cursor->next && !get_term()->cursor->prev
		&& buf == K_CTRL_D)
		return (0);
	else if (get_term()->cursor->next)
	{
		get_term()->cursor = get_term()->cursor->next;
		ft_curright(1);
		ft_back_space();
	}
	else
		ft_dprintf(0, "\a");
	return (1);
}

void	ft_back_space(void)
{
	if (!line_bs(get_term()->cursor))
	{
		ft_curleft(1);
		tputs(tparm(get_term()->del_ch, 1), 1, term_print);
		ft_print_tail(get_term()->cursor);
	}
	else
		ft_dprintf(0, "\a");
}

void	ft_move(uint64_t buf)
{
	int	i;

	i = (buf == K_LEFT || buf == K_RIGHT) ? get_term()->width - 1 : 0;
	if ((buf == K_LEFT || buf == K_AUP || buf == K_HOME)
		&& get_term()->cursor->prev)
		while (i < get_term()->width && get_term()->cursor->prev)
		{
			buf == K_HOME ? 0 : i++;
			ft_curleft(1);
			get_term()->cursor = get_term()->cursor->prev;
		}
	else if ((buf == K_RIGHT || buf == K_ADOWN || buf == K_END)
			&& get_term()->cursor->next)
		while (i < get_term()->width && get_term()->cursor->next)
		{
			buf == K_END ? 0 : i++;
			ft_curright(1);
			get_term()->cursor = get_term()->cursor->next;
		}
	else
		ft_dprintf(0, "\a");
}

void	ft_word_action(uint64_t buf)
{
	int		flag;
	t_line	*cursor;

	flag = 0;
	while ((cursor = (buf == K_ARIGHT || buf == K_ADEL)
			? get_term()->cursor : get_term()->cursor->prev)
			&& (buf == K_ALEFT || buf == K_ABS || cursor->next)
			&& !(ft_iswhitespace(cursor->ch) && flag))
	{
		!ft_iswhitespace(cursor->ch) ? flag = 1 : 0;
		if (buf == K_ALEFT || buf == K_ARIGHT)
			ft_move(buf == K_ALEFT ? K_LEFT : K_RIGHT);
		else
			buf == K_ABS ? ft_back_space() : ft_del(K_DEL);
	}
	if (!flag)
		ft_dprintf(0, "\a");
}

int		ft_add(uint64_t buf)
{
	int	ret;

	ret = 1;
	ft_dprintf(0, "%s", &buf);
	ft_curright(0);
	ret = line_add(get_term()->cursor, buf);
	get_term()->cursor->ch ? ft_print_tail(get_term()->cursor) : 0;
	return (ret);
}
