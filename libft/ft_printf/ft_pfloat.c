/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfloat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:16:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/29 21:11:05 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static void	ft_pfd(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];
	double	nbr;
	char	*f;

	nbr = va_arg(*ap, double);
	if (nbr != nbr)
		tmp[2] = arg->spec == 'f' ? ft_strdup("nan") : ft_strdup("NAN");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'f')
		tmp[2] = nbr < 0 ? ft_strdup("-inf") : ft_strdup("inf");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'F')
		tmp[2] = nbr < 0 ? ft_strdup("-INF") : ft_strdup("INF");
	else
		tmp[2] = ft_dtoa(nbr, arg->is_prec ? arg->prec : 6,
						ft_strchr(arg->flags, '#') != 0);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	(*tmp[2] == '-') ? len[0]-- : 0;
	arg->is_prec = 0;
	if ((nbr != nbr || nbr == 1.0 / 0.0) && (f = ft_strchr(arg->flags, '0')))
		*f = 'r';
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

inline static void	ft_plfd(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	char		*tmp[3];
	int			len[2];
	long double	nbr;
	char		*f;

	nbr = va_arg(*ap, long double);
	if (nbr != nbr)
		tmp[2] = arg->spec == 'f' ? ft_strdup("nan") : ft_strdup("NAN");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'f')
		tmp[2] = nbr < 0 ? ft_strdup("-inf") : ft_strdup("inf");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'F')
		tmp[2] = nbr < 0 ? ft_strdup("-INF") : ft_strdup("INF");
	else
		tmp[2] = ft_ldtoa(nbr, arg->is_prec ? arg->prec : 6,
						ft_strchr(arg->flags, '#') != 0);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	(*tmp[2] == '-') ? len[0]-- : 0;
	arg->is_prec = 0;
	if ((nbr != nbr || nbr == 1.0 / 0.0) && (f = ft_strchr(arg->flags, '0')))
		*f = 'r';
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

inline static void	ft_pefd(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];
	double	nbr;
	char	*f;

	nbr = va_arg(*ap, double);
	if (nbr != nbr)
		tmp[2] = arg->spec == 'e' ? ft_strdup("nan") : ft_strdup("NAN");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'e')
		tmp[2] = nbr < 0 ? ft_strdup("-inf") : ft_strdup("inf");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'E')
		tmp[2] = nbr < 0 ? ft_strdup("-INF") : ft_strdup("INF");
	else
		tmp[2] = ft_dtoea(nbr, arg->is_prec ? arg->prec : 6,
							ft_strchr(arg->flags, '#') != 0, arg->spec);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	(*tmp[2] == '-') ? len[0]-- : 0;
	arg->is_prec = 0;
	if ((nbr != nbr || nbr == 1.0 / 0.0) && (f = ft_strchr(arg->flags, '0')))
		*f = 'r';
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

inline static void	ft_pelfd(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	char		*tmp[3];
	int			len[2];
	long double	nbr;
	char		*f;

	nbr = va_arg(*ap, long double);
	if (nbr != nbr)
		tmp[2] = arg->spec == 'e' ? ft_strdup("nan") : ft_strdup("NAN");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'e')
		tmp[2] = nbr < 0 ? ft_strdup("-inf") : ft_strdup("inf");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'E')
		tmp[2] = nbr < 0 ? ft_strdup("-INF") : ft_strdup("INF");
	else
		tmp[2] = ft_ldtoea(nbr, arg->is_prec ? arg->prec : 6,
							ft_strchr(arg->flags, '#') != 0, arg->spec);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	(*tmp[2] == '-') ? len[0]-- : 0;
	arg->is_prec = 0;
	if ((nbr != nbr || nbr == 1.0 / 0.0) && (f = ft_strchr(arg->flags, '0')))
		*f = 'r';
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

inline void			ft_pfloat(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	if (arg->spec == 'f' || arg->spec == 'F')
	{
		if (arg->len && arg->len[0] == 'L')
			ft_plfd(pbuf, ap, arg);
		else
			ft_pfd(pbuf, ap, arg);
	}
	else if (arg->spec == 'e' || arg->spec == 'E')
	{
		if (arg->len && arg->len[0] == 'L')
			ft_pelfd(pbuf, ap, arg);
		else
			ft_pefd(pbuf, ap, arg);
	}
}
