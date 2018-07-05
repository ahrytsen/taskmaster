/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:35:29 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 17:11:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

static void	sig_handler(int signo)
{
	struct winsize	w;

	if (signo == SIGWINCH)
	{
		ft_curhome();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		get_term()->height = w.ws_row;
		get_term()->width = w.ws_col;
		ft_redraw_line();
	}
	else if (signo == SIGTSTP)
		ft_dprintf(2, "\a");
}

static void	ft_set_rl_signal(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGTSTP, sig_handler);
}

static void	ft_init_termcap(void)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		ft_fatal(1, exit,
				"Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal(1, exit, "Could not access the termcap data base.\n");
	else if (!success)
		ft_fatal(1, exit, "Terminal type `%s' is not defined.\n", termtype);
	get_term()->clear = tgetstr("ce", NULL);
	get_term()->cm_left = tgetstr("le", NULL);
	get_term()->cm_right = tgetstr("nd", NULL);
	get_term()->iv_on = tgetstr("mr", NULL);
	get_term()->iv_off = tgetstr("me", NULL);
	get_term()->del_ch = tgetstr("DC", NULL);
	get_term()->height = tgetnum("li");
	get_term()->width = tgetnum("co");
}

void		ft_terminal(int mod)
{
	static int	already_saved = 0;

	if (!isatty(0))
		ft_fatal(1, exit, "taskmaster: fd isn't valid terminal type device.\n");
	else if (mod == T_INIT && !already_saved)
	{
		ft_bzero(get_term(), sizeof(t_term));
		ft_init_termcap();
		tcgetattr(0, &get_term()->savetty);
		get_term()->work_tty = get_term()->savetty;
		get_term()->work_tty.c_lflag &= ~(ICANON | ECHO);
		get_term()->work_tty.c_lflag |= TOSTOP;
		get_term()->work_tty.c_cc[VMIN] = 1;
		get_term()->work_tty.c_cc[VTIME] = 0;
		already_saved = 1;
	}
	if (mod == T_INIT)
	{
		ft_set_rl_signal();
		tcsetattr(0, TCSAFLUSH, &get_term()->work_tty);
	}
	else
		tcsetattr(0, TCSANOW, &get_term()->savetty);
}
