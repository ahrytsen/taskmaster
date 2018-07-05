/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/05 17:09:50 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_readline.h>

int	main(void)
{
	char	*line;

	while (ft_readline(0, &line) > 0)
	{
		ft_printf("line: %s\n", line);
		free(line);
	}
}
