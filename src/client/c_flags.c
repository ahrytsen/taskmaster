/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_flags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:27:05 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/20 11:06:19 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

static void	c_usage(char *av)
{
	ft_dprintf(2,
	"taskmasterctl -- control applications run by taskmasterd"
	"from the cmd line.\n"
	"\nUsage: %s [options]\n"
	"\nOptions:\n"
	"-h -- print this usage message and exit\n"
	"-s -- URL on which taskmasterd server is listening\n"
	"\t(default \"http://localhost:7279\")\n",
			av);
	exit(1);
}

static int	check_regex(const char *pattern, char *s)
{
	regex_t	re;
	int		ret;

	ret = 0;
	if (regcomp(&re, pattern, REG_EXTENDED) == 0)
		if (regexec(&re, s, 0, NULL, 0) == 0)
			ret = 1;
	regfree(&re);
	return (ret);
}

static void	record_url(char *s)
{
	const char	*pattern_domain = "^https?:\\/\\/[a-zA-Z0-9.]+:[0-9]{1,5}$";
	const char	*pattern_ip = "^https?:\\/\\/((25[0-5]|2[0-4][0-9]|1[0-9][0-9]"

	"|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1"
	"[0-9][0-9]|[1-9]?[0-9]):[0-9]{1,5}$";
	if (s == NULL)
		ft_fatal(EXIT_FAILURE, exit, "Error: option -s requires argument\n");
	if (check_regex(pattern_ip, s))
		get_cconf()->type = ip;
	else if (check_regex(pattern_domain, s))
		get_cconf()->type = domain;
	else
	{
		ft_fatal(EXIT_FAILURE, exit, "Bad URL\n");
		return ;
	}
	get_cconf()->port = ft_atoi(ft_strrchr(s, ':') + 1);
	get_cconf()->addr = s;
	*ft_strrchr(s, ':') = '\0';
	get_cconf()->addr = ft_strrchr(s, '/') + 1;
}

void		check_flags(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
		if (*av[i] == '-')
			while (*++av[i])
			{
				if (*av[i] == 's')
				{
					record_url(*++av[i] ? av[i] : av[++i]);
					break ;
				}
				else if (*av[i] == 'h')
					c_usage(*av);
				else
					ft_fatal(1, exit, "Error: option -%c not recognized\n"
							"For help, use %s -h\n", *av[i], *av);
			}
		else
			ft_fatal(1, exit, "Error: unexpected parameter: %s\n"
					"For help, use %s -h\n", av[i], *av);
}
