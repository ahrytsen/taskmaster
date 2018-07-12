/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/10 21:37:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <locale.h>
# include "libft.h"

# define PBS 8192

typedef struct	s_len
{
	int		k;
	char	*len;
}				t_len;
typedef struct	s_buf
{
	size_t			id;
	size_t			len;
	char			*str;
	struct s_buf	*next;
}				t_buf;
typedef struct	s_color
{
	char	*color_name;
	char	*color_cod;
}				t_color;
typedef struct	s_conv
{
	char	*conv;
	void	(*ft_phelper)();
}				t_conv;
typedef struct	s_arg
{
	char		flags[6];
	ssize_t		width;
	int			is_prec;
	ssize_t		prec;
	int			k;
	const char	*len;
	char		spec;
}				t_arg;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
void			ft_fatal(int st, void (*exit_f)(int), const char *format, ...);
int				ft_asprintf(char **line, const char *format, ...);

const char		*ft_get_format(va_list *ap, const char *format, t_arg *arg);
void			ft_get_color(const char **format, t_buf **pbuf);
/*
**				Buffer managment!
*/
t_buf			*ft_newbuf(void);
void			ft_putchar_buf(t_buf **pbuf, int c);
void			ft_putustr_buf(t_buf **pbuf, int *str, ssize_t len);
void			ft_putstr_buf(t_buf **pbuf, char *str, ssize_t len);
ssize_t			ft_print_buf(int fd, t_buf *pbuf, t_buf *pbuf_head);
ssize_t			ft_buftostr(char **line, t_buf *pbuf, t_buf *pbuf_head);
/*
**				Helpers!
*/
int				ft_get_len(const char **format, t_arg *arg);
void			ft_get_width(const char **format, va_list *ap, t_arg *arg);
void			ft_get_prec(const char **format, va_list *ap, t_arg *arg);
void			ft_filler(t_buf **pbuf, t_arg *arg, ssize_t width);
long			ft_getnbr(va_list *ap, t_arg *arg);
void			ft_print_arg(t_buf **pbuf, t_arg *arg, char **tmp, int *len);
/*
**				Conversion hendlers!
*/
void			ft_str(t_buf **pbuf, va_list *ap, t_arg *arg);
void			ft_int(t_buf **pbuf, va_list *ap, t_arg *arg);
void			ft_base(t_buf **pbuf, va_list *ap, t_arg *arg);
void			ft_undef(t_buf **pbuf, va_list *ap, t_arg *arg);
void			ft_pfloat(t_buf **pbuf, va_list *ap, t_arg *arg);

#endif
