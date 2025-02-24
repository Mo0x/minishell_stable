/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_get_command_as_asttree.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:23:15 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:24:07 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <fcntl.h>

t_asttree	*get_node_from_lst(t_list *lst)
{
	if (lst->data_type == INT_TYPE)
		return (asttree_create_node(REDIRECTION, \
						get_redirect_data(lst->content.int_val), \
										NULL));
	if (lst->data_type == STR_TYPE)
		return (asttree_create_node(is_builtin(lst->content.str_val), \
											lst->content.str_val, NULL));
	return (NULL);
}

t_list	*convert_lst_to_readable_lparam_for_exec(t_list	*lst)
{
	char	*buf;
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		if (lst->data_type == INT_TYPE && \
			get_redirect_data(lst->content.int_val))
		{
			allocchk(buf = ft_strdup(get_redirect_data(lst->content.int_val), \
			SAFE));
			lst->data_type = STR_TYPE;
			lst->content.str_val = buf;
		}
		lst = lst->next;
	}
	return (tmp);
}

t_asttree	*return_pure_node(t_list *lst)
{
	t_asttree	*node;

	node = asttree_create_node(is_builtin(lst->content.str_val), \
							lst->content.str_val, NULL);
	node->l_param = lst;
	return (node);
}

// the lst is split as a tab of lst. When a logical, sound prompt is entered,
// lst_split[0] is the command and the rest its childrens.
// TODO : echo merde | > file1 (ou le dégager au parsing ?)
t_asttree	*get_command_as_asttree(t_list *lst)
{
	int			redirect_count;
	t_list		**lst_split;
	t_asttree	*node;
	t_asttree	*child;
	int			i;

	if (lst == NULL)
		return (NULL);
	flag_lstnodes(lst);
	cmd_join(&lst);
	redirect_count = lst_redirects_count(lst);
	if (!redirect_count)
		return (return_pure_node(lst));
	lst_split = split_lst_at_redirection(&lst, redirect_count);
	node = get_node_from_lst(lst_split[0]);
	node->l_param = lst_split[0];
	i = 1;
	while (lst_split[i])
	{
		child = get_node_from_lst(lst_split[i]);
		child->l_param = convert_lst_to_readable_lparam_for_exec(lst_split[i]);
		asttree_addchild(node, child);
		i++;
	}
	return (node);
}
