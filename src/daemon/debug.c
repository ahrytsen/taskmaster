#include <daemon.h>

void		output_parse_tree(t_list *parse_lst)
{
	while (parse_lst)
	{
		ft_printf("Key:   %s\n", ((t_yaml_tree *)(parse_lst->content))->key);
		if (((t_yaml_tree *)(parse_lst->content))->type == singular_val)
			ft_printf("Value: %s\n", ((t_yaml_tree *)(parse_lst->content))->value->content);
		else if (((t_yaml_tree *)(parse_lst->content))->type == mapping_val)
		{
			ft_printf("Value:\n----MAPPING----\n");
			output_parse_tree(((t_yaml_tree *)(parse_lst->content))->value);
			ft_printf("----END OF MAPPING----\n");
		}
		else if (((t_yaml_tree *)(parse_lst->content))->type == sequence_val)
		{
			ft_printf("Values:\n----SEQUENCE----\n");
			t_list *tmp = ((t_yaml_tree *)(parse_lst->content))->value;
			while (tmp)
			{
				ft_printf("\t- %s\n", tmp->content);
				tmp = tmp->next;
			}
			ft_printf("----END OF SEQUENCE----\n");
		}
		parse_lst = parse_lst->next;
	}
}

void	outputs()
{
	t_list *tmp = get_dconf()->proc;

	ft_printf("\n\tRECORDED INFO\n");
	while (tmp)
	{
		ft_printf("name: %s\n", ((t_proc *)(tmp->content))->name);
		if (((t_proc *)(tmp->content))->argv)
		{
			int i = -1;
			while (((t_proc *)(tmp->content))->argv[++i])
				ft_printf("argv[%i]: %s\n", i, ((t_proc *)(tmp->content))->argv[i]);
		}
		ft_printf("numproc: %i\n", ((t_proc *)(tmp->content))->numprocs);
		ft_printf("umask: %i\n", ((t_proc *)(tmp->content))->umask);
		ft_printf("workingdir: %s\n", ((t_proc *)(tmp->content))->workingdir);
		ft_printf("autostart: %i\n", ((t_proc *)(tmp->content))->autostart);
		ft_printf("autorestart: %i\n", ((t_proc *)(tmp->content))->autorestart);
		ft_printf("starttime: %i\n", ((t_proc *)(tmp->content))->starttime);
		ft_printf("startretries: %i\n", ((t_proc *)(tmp->content))->startretries);
		ft_printf("stdout: %s\n", ((t_proc *)(tmp->content))->stdout);
		ft_printf("stderr: %s\n", ((t_proc *)(tmp->content))->stderr);
		ft_printf("stopsignal: %i\n", ((t_proc *)(tmp->content))->stopsignal);
		for (int i = 0; i < 255; i++)
			if (((t_proc *)(tmp->content))->exitcodes[i])
				ft_printf("exitcode: %i\n", i);
		ft_printf("env:\n");
		char **tmp2 = ((t_proc *)(tmp->content))->env;
		if (tmp2)
			while (*tmp2)
				ft_printf("\t%s\n", *tmp2++);
		tmp = tmp->next;
		ft_printf("\n--------------\n\n");
	}
	ft_printf("logout: %s\n", get_dconf()->out_log);
	ft_printf("logerr: %s\n", get_dconf()->err_log);
	ft_printf("ip: %s\n", get_dconf()->ip);
	ft_printf("port: %i\n", get_dconf()->port);
}