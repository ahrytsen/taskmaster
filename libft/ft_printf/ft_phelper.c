/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 14:03:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/29 14:51:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static t_len	g_len[] =
{
	{1, "hh"}, {2, "h"}, {4, "ll"}, {3, "l"},
	{5, "j"}, {6, "t"}, {7, "z"}, {8, "L"}, {0, NULL}
};

inline int	ft_get_len(const char **format, t_arg *arg)
{
	int	i;

	i = 0;
	while (g_len[i].len
			&& ft_strncmp(g_len[i].len, *format, ft_strlen(g_len[i].len)))
		i++;
	if (arg->k < g_len[i].k)
	{
		arg->len = g_len[i].len;
		arg->k = g_len[i].k;
	}
	*format += g_len[i].len ? ft_strlen(g_len[i].len) - 1 : 0;
	return (g_len[i].len ? 1 : 0);
}

inline void	ft_get_width(const char **format, va_list *ap, t_arg *arg)
{
	if (**format == '*')
		arg->width = va_arg(*ap, int);
	else if (**format >= '0' && **format <= '9')
	{
		arg->width = ft_atol(*format);
		while (*(*format + 1) >= '0' && *(*format + 1) <= '9')
			(*format)++;
	}
}

inline void	ft_get_prec(const char **format, va_list *ap, t_arg *arg)
{
	if (*(*format + 1) == '*')
	{
		(*format)++;
		arg->prec = va_arg(*ap, int);
	}
	else
	{
		arg->prec = ft_atol(*format + 1);
		while (*(*format + 1) >= '0' && *(*format + 1) <= '9')
			(*format)++;
	}
	arg->prec >= 0 ? arg->is_prec = 1 : 0;
}

inline void	ft_filler(t_buf **pbuf, t_arg *arg, ssize_t width)
{
	char	filler;

	filler = (!(arg->is_prec && ft_strchr("diDuUpoObxX", arg->spec))
			&& !ft_strchr(arg->flags, '-') && arg->width >= 0
			&& ft_strchr(arg->flags, '0')) ? '0' : ' ';
	while (width-- > 0)
		ft_putchar_buf(pbuf, filler);
}

inline long	ft_getnbr(va_list *ap, t_arg *arg)
{
	long	nbr;

	nbr = (ft_strchr("pDUO", arg->spec)
			|| (arg->len && ft_strchr("lzjt", arg->len[0])))
		? va_arg(*ap, long) : (unsigned int)va_arg(*ap, int);
	if (ft_strchr("pDUO", arg->spec)
		|| (arg->len && ft_strchr("lzjt", arg->len[0])))
		return (nbr);
	if (arg->len && !ft_strcmp("hh", arg->len))
		nbr = ft_strchr("di", arg->spec) ? (char)nbr : (unsigned char)nbr;
	else if (arg->len && !ft_strcmp("h", arg->len))
		nbr = ft_strchr("di", arg->spec) ? (short)nbr : (unsigned short)nbr;
	else
		ft_strchr("di", arg->spec) ? nbr = (int)nbr : 0;
	return (nbr);
}
