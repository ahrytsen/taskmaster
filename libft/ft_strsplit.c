/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:29:32 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/16 14:00:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	int		m;
	size_t	res;

	m = 0;
	res = 0;
	while (*s)
	{
		if (*s != c && !m)
		{
			m = 1;
			res++;
		}
		else if (*s == c && m)
			m = 0;
		s++;
	}
	return (res);
}

static void		ft_freesplit(char **split, size_t i)
{
	while (i--)
		free(split[i]);
	free(split);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	wlen;
	char	**split;

	i = 0;
	if (!s ||
		!(split = (char**)malloc((ft_countwords(s, c) + 1) * sizeof(char*))))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			wlen = ft_strlen_c(s, c);
			if (!(split[i++] = ft_strsub(s, 0, wlen)))
			{
				ft_freesplit(split, --i);
				return (NULL);
			}
			s += wlen;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}
