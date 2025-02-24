/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_get_command_node_tab.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:34 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:24:35 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_logicaltree	*single_command(t_list *lst, t_logicaltree *tree)
{
	tree->size = 1;
	allocchk(tree->logicaltree = walloc(sizeof(t_asttree **), SAFE));
	tree->logicaltree[0] = single_command_logic(lst);
	return (tree);
}

// In case of multi-commands prompt, a loop is used to retrieve every
// commands as asttree*, filling tab.
// size and i are here to accomodate the norm.
// they are initialised to 0.
t_logicaltree	*get_commands_nodes_tab(t_list *lst, int size, int i)
{
	t_logicaltree	*tree;
	t_asttree		**tab;
	t_asttree		*node;
	t_list			*tmp;

	allocchk(tree = walloc(sizeof(t_logicaltree), SAFE));
	tmp = lst;
	size = get_number_of_inttypes_nonredirect_tokens(lst);
	lst = tmp;
	if (size == 0)
		return (single_command(lst, tree));
	size += 2;
	allocchk(tab = walloc((size + 1) * sizeof(t_asttree *), SAFE));
	while (1)
	{
		node = create_cmd_node(&lst);
		if (lst)
			lst = lst->next;
		tab[i] = node;
		i++;
		if (node == NULL)
			break ;
	}
	return (tree->size = size, tree->logicaltree = tab, tree);
}

// The static is important here : when the logic goes on to the NULL lst,
// we need to return the last command of the prompt, and then return a NULL
// the next time the function is called
// important ! the if (list) line checks if there is actually a command
// to return when encountering an operator. this little bastard consumed
// 2 of my mortal days. because otherwise getcommand will return NULL 
// even though
// the debugger says the local lst is not NULL;
t_asttree	*create_cmd_node(t_list **lst)
{
	t_list		*list;
	static int	end_of_list = 0;

	list = NULL;
	while ((*lst))
	{
		if ((*lst)->data_type == INT_TYPE && \
			!get_redirect_data((*lst)->content.int_val))
		{
			end_of_list = 0;
			if (list)
				return (get_command_as_asttree(list));
		}
		else
		{
			if (!list)
				list = lstdup(*lst);
			else
				ft_lstadd_back(&list, lstdup(*lst));
		}
		(*lst) = (*lst)->next;
	}
	if (end_of_list == 0)
		return (end_of_list = 1, get_command_as_asttree(list));
	return (end_of_list = 0, NULL);
}
