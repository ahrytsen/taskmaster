/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 17:47:43 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/16 11:32:59 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKMASTER_CLIENT_H
# define TASKMASTER_CLIENT_H

# include <libft.h>
# include <ft_readline.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <errno.h>
# include <regex.h>
# include <arpa/inet.h>
# include <netdb.h>

typedef struct	s_cconf
{
	uint16_t	port;
	char		*addr;
	enum 		e_type
	{
		domain,
		ip
	}			type;
}				t_cconf;

/*
**				main.c
*/
t_cconf			*get_cconf(void);
/*
**				c_flags.c
*/
void			check_flags(int ac, char **av);
/*
**				../exchange.c
*/
void send_msg(int sock, char *msg);
ssize_t			receive_msg(char **line, int sock);
#endif
