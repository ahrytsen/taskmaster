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