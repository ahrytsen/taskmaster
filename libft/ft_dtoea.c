/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 19:48:37 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/29 21:51:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_exp(double *nbr, char c)
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

char			*ft_dtoea(double nbr, int precision, int dot, char c)
{
	char	*snbr;
	char	*exp;

	exp = ft_exp(&nbr, c);
	snbr = ft_dtoa(nbr, precision, dot);
	snbr = ft_strextend(snbr, exp);
	return (snbr);
}
