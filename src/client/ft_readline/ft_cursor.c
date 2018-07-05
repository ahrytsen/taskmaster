/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:38:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 17:28:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

void	ft_curhome(void)
{
	tputs(tgetstr("cd", NULL), 1, term_print);
	while (get_term()->curx || get_term()->cury)
		ft_curleft(1);
	ft_prompt();
}

void	ft_curleft(int mod)
{
	if (get_term()->curx == 0 && get_term()->cury >= 0)
	{
		get_term()->curx = get_term()->width - 1;
		get_term()->cury--;
		tputs(tgetstr("up", NULL), 1, term_print);
		tputs(tgoto(tgetstr("ch", NULL), 1, get_term()->width - mod),
			1, term_print);
	}
	else if (get_term()->cury >= 0)
	{
		get_term()->curx--;
		mod ? tputs(tgoto(get_term()->cm_left, 1, 1), 1, term_print) : 0;
	}
}

void	ft_curright(int mod)
{
	if (get_term()->curx == get_term()->width - 1)
	{
		get_term()->curx = 0;
		get_term()->cury++;
		tputs(tgetstr("do", NULL), 1, term_print);
		tputs(tgetstr("cr", NULL), 1, term_print);
		!mod ? tputs(tgetstr("cd", NULL), 1, term_print) : 0;
	}
	else if (get_term()->cury >= 0)
	{
		get_term()->curx++;
		mod ? tputs(get_term()->cm_right, 1, term_print) : 0;
	}
}

void	ft_curnleft(int mod, int n)
{
	while (n--)
		ft_curleft(mod);
}

void	ft_curnright(int mod, int n)
{
	while (n--)
		ft_curright(mod);
}
