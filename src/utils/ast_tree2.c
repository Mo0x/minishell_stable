/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:31:27 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:39:46 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	asttree_postorder_clear(t_asttree *node, void (*f)(t_asttree *))
{
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	while (++i < node->num_child)
		asttree_postorder_clear(node->children[i], f);
}

void	asttree_clear(t_asttree *root)
{
	asttree_postorder_clear(root, asttree_delete_node);
	asttree_delete_node(root);
}

void	ft_freetab(void **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		wfree(to_free[i]);
		i++;
	}
	wfree(to_free[i]);
}

char	*convert_type(t_nodetype type)
{
	if (type == BUILTIN)
		return ("BUILTIN");
	if (type == COMMAND)
		return ("COMMAND");
	if (type == AND_OP)
		return ("AND_OP");
	if (type == OR_OP)
		return ("OR_OP");
	if (type == PIPE_OP)
		return ("PIPE_OP");
	if (type == REDIRECTION)
		return ("REDIRECTION");
	if (type == SUBTREE)
		return ("SUBTREE");
	if (type == ERROR)
		return ("ERROR");
	if (type == TMP_SUBTREE)
		return ("TMP SUBTREE");
	if (type == VOID)
		return ("VOID");
	return ("ERROR");
}

int	is_logical_node(t_asttree *node)
{
	return (node->type == PIPE_OP || node->type == AND_OP
		|| node->type == OR_OP);
}
