/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:40:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/23 15:31:19 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

t_cconf		*get_cconf(void)
{
	static t_cconf	cconf;

	return (&cconf);
}

static void	get_response(int sock)
{
	ssize_t	ret;
	char	*msg;

	while ((ret = receive_msg(&msg, sock)) > 0)
	{
		if (msg)
			ft_dprintf(1, "%s", msg);
		free(msg);
	}
	if (ret < 0)
		ft_fatal(EXIT_FAILURE, exit, "%s\n", strerror(errno));
}

static int	send_commands(char **cmds, int sock)
{
	int		i;
	int		ret;
	char	*tmp;

	i = -1;
	ret = 0;
	while (cmds[++i])
	{
		tmp = cmds[i];
		cmds[i] = ft_strtrim(cmds[i]);
		free(tmp);
		if (!ft_strncmp(cmds[i], "exit", 4) && (cmds[i][4] == ' ' ||
												cmds[i][4] == '\0'))
		{
			ret = 1;
			break ;
		}
		send_msg(sock, cmds[i]);
		get_response(sock);
	}
	ft_strarr_free(cmds);
	return (ret);
}

int			main(int ac, char **av)
{
	char	*line;
	int		sock;
	char	**cmds;

	ft_bzero(get_cconf(), sizeof(t_cconf));
	check_flags(ac, av);
	sock = socket_connect();
	while (ft_readline(0, &line) > 0)
	{
		cmds = ft_strsplit(line, ';');
		free(line);
		if (cmds && send_commands(cmds, sock) == 1)
			break ;
	}
	close(sock);
	return (0);
}
