/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:31:00 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 15:08:48 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

uint64_t	ft_highlight_helper(uint64_t buf)
{
	if ((buf != K_SLEFT && buf != K_SRIGHT && buf != K_SUP
		&& buf != K_SDOWN && buf != K_ASLEFT && buf != K_ASRIGHT
		&& (get_term()->st_sel || get_term()->end_sel)) || buf == K_PASTE)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		buf != K_RET ? ft_redraw_line() : 0;
	}
	return (buf);
}

void		ft_highlight(uint64_t buf)
{
	if (!get_term()->st_sel && !get_term()->end_sel)
		get_term()->st_sel = get_term()->cursor;
	if (buf == K_SRIGHT || buf == K_SDOWN)
		ft_move(buf == K_SRIGHT ? K_RIGHT : K_ADOWN);
	else if (buf == K_SLEFT || buf == K_SUP)
		ft_move(buf == K_SLEFT ? K_LEFT : K_AUP);
	else
		ft_word_action(buf == K_ASRIGHT ? K_ARIGHT : K_ALEFT);
	get_term()->end_sel = get_term()->cursor;
	if (get_term()->st_sel == get_term()->end_sel)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
	}
	ft_redraw_line();
}
