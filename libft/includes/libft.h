/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 05:35:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/14 16:01:29 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>

# define MOD(a)(a >= 0 ? a : -a)

/*
**				ft_printf
*/
int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
void			ft_fatal(int st, void (*exit_f)(int), const char *format, ...);
int				ft_asprintf(char **line, const char *format, ...);
/*
**				Get_Next_Line
*/
# define BUFF_SIZE 32

int				get_next_line(const int fd, char **line);
/*
**				Part 1 - Libc functions
*/
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
/*
**				Part 2 - Additional functions
*/
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
int				ft_putchar(int c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
/*
**				Bonus part
*/
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
/*
**              Extra functions
*/
void			ft_lstadd_end(t_list **alst, t_list *new);
t_list			*ft_lstpush_back(t_list **lst, void const *content,
								size_t content_size);
t_list			*ft_lstpush_front(t_list **lst, void const *content,
								size_t content_size);
t_list			*ft_lstsplit(char const *s, char c);
size_t			ft_strlen_c(char const *s, char c);
int				ft_wcharlen(int c);
size_t			ft_strulen(int *s);
char			*ft_strextend(char *s1, char *s2);
char			*ft_strhalfextend(char *s1, char *s2);
char			*ft_ultoa_base(size_t value, int base, char st_l);
long			ft_atol(const char *str);
char			*ft_ltoa(long value);
char			*ft_dtoa(double nbr, int precision, int dot);
char			*ft_ldtoa(long double nbr, int precision, int dot);
char			*ft_dtoea(double nbr, int precision, int dot, char c);
char			*ft_ldtoea(long double nbr, int precision, int dot, char c);
void			ft_sort_params(char **av, int ac);
char			**ft_strdup_arr(char **src_arr);
int				ft_iswhitespace(int c);
int				ft_isalpha_str(char *str);
int				ft_isnumeric_str(char *str);
int				ft_isalnum_str(char *str);
int				ft_isascii_str(char *str);
int				ft_isprint_str(char *str);
long			ft_atol_base(const char *str, int base);
int				ft_atoi_base(const char *str, int base);
void			ft_strarr_free(char **arr);
char			*ft_arrstr(char **arr, char *str);
size_t			ft_count_digits(size_t n);

#endif
