/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 19:08:34 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 21:37:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern const t_conv	g_phelper[];

void	ft_fatal(int st, void (*exit_f)(int), const char *format, ...)
{
	t_arg		arg;
	va_list		ap;
	t_buf		*pbuf[2];
	int			i;

	pbuf[0] = format ? ft_newbuf() : NULL;
	format ? va_start(ap, format) : 0;
	pbuf[1] = pbuf[0];
	while (pbuf[1] && *format)
		if (*format == '%' && !(i = 0))
		{
			format = ft_get_format(&ap, format + 1, &arg);
			while (g_phelper[i].conv && !ft_strchr(g_phelper[i].conv, arg.spec))
				i++;
			(!arg.spec || !g_phelper[i].conv) ? ft_undef(&pbuf[1], &ap, &arg)
				: g_phelper[i].ft_phelper(&pbuf[1], &ap, &arg);
		}
		else if (*format == '{')
			ft_get_color(&format, &pbuf[1]);
		else
			ft_putchar_buf(&pbuf[1], *format++);
	format ? va_end(ap) : 0;
	ft_print_buf(2, pbuf[1], pbuf[0]);
	exit_f(st);
}
