/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_asttree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:10:06 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:11:30 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// USELESS
t_asttree	*single_command_logic(t_list *lst)
{
	return (get_command_as_asttree(lst));
}

// first two tabs of asttree* are created,
// one for the logical operator (AND OR PIPE)
// and one for the commands. They are then simply linked together and returned.
t_asttree	*convert_list_to_asttree(t_msh *msh, t_list **lst, \
									int has_parenthesis)
{
	t_logicaltree	*logicaltree;
	t_logicaltree	*cmdtree;

	(void)msh;
	logicaltree = get_logical_nodes_tab(*lst, 0, 0);
	cmdtree = get_commands_nodes_tab(*lst, 0, 0);
	if (!has_parenthesis)
		return (join_trees_no_parenthesis(logicaltree, cmdtree));
	else
		return (join_trees_with_parenthesis(logicaltree, cmdtree));
	return (NULL);
}
