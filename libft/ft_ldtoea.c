/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoea.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 20:21:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/29 21:51:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_exp(long double *nbr, char c)
{
	int		i;
	char	*ichar;
	char	*ret;

	i = 0;
	while ((long)(*nbr))
	{
		*nbr /= 10.0;
		i++;
	}
	while (!((long)(*nbr)) && *nbr != 0.0)
	{
		*nbr *= 10.0;
		i--;
	}
	ichar = ft_itoa(MOD(i));
	ret = (char*)ft_memalloc(3 + ((i > 9 || i < -9) ? ft_strlen(ichar) : 2));
	*ret = c;
	ret[1] = i < 0 ? '-' : '+';
	ret[2] = '0';
	(i > 9 || i < -9) ? ft_strcpy(ret + 2, ichar) : ft_strcpy(ret + 3, ichar);
	free(ichar);
	return (ret);
}

char				*ft_ldtoea(long double nbr, int precision, int dot, char c)
{
	char	*snbr;
	char	*exp;

	exp = ft_exp(&nbr, c);
	snbr = ft_ldtoa(nbr, precision, dot);
	snbr = ft_strextend(snbr, exp);
	return (snbr);
}
