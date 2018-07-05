/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:35:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 15:35:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int		term_print(int c)
{
	return (write(0, &c, 1));
}

t_term	*get_term(void)
{
	static t_term	term;

	return (&term);
}

void	ft_readline_ret(void)
{
	while (get_term()->cursor->next
			&& (get_term()->cursor = get_term()->cursor->next))
		ft_curright(1);
	ft_dprintf(0, "\n");
}

void	ft_redraw_line(void)
{
	t_line	*cursor;
	uint8_t	f;
	int		count;

	cursor = get_term()->cursor;
	f = 0;
	count = 0;
	ft_curhome();
	while (cursor->prev && (cursor = cursor->prev))
		--count;
	while (cursor->next)
	{
		if (cursor == get_term()->st_sel || cursor == get_term()->end_sel)
		{
			tputs(!f ? get_term()->iv_on : get_term()->iv_off, 1, term_print);
			f = !f;
		}
		ft_dprintf(0, "%s", &cursor->ch);
		ft_curright(0);
		cursor = cursor->next;
		count++;
	}
	ft_curnleft(1, count);
	f ? tputs(get_term()->iv_off, 1, term_print) : 0;
}

void	ft_print_tail(t_line *cursor)
{
	int	count;

	count = 0;
	while (cursor->next)
	{
		ft_dprintf(0, "%s", &cursor->ch);
		ft_curright(0);
		cursor = cursor->next;
		count++;
	}
	tputs(get_term()->clear, 1, term_print);
	ft_curnleft(1, count);
}
