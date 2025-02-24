/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_join_with_parenthesis.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:25:51 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:52 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	index_last_logical_node(t_asttree *n)
{
	int	i;
	int	j;
	int	has_logical_children;

	j = 0;
	i = -1;
	has_logical_children = 0;
	while (j < n->num_child)
	{
		if (is_logical_node(n->children[j]))
			has_logical_children = 1;
		j++;
	}
	if (!has_logical_children)
		n->is_last_logical_node = 1;
	while (++i < n->num_child)
	{
		index_last_logical_node(n->children[i]);
	}
}

void	check_if_logical_nodes_need_tmpsubtrees(t_asttree *n)
{
	int			i;
	t_asttree	*tmpsubtree;

	i = -1;
	if (is_logical_node(n) && !n->is_last_logical_node && n->num_child == 1)
	{
		tmpsubtree = asttree_create_node(TMP_SUBTREE, NULL, NULL);
		tmpsubtree->index = 0;
		tmpsubtree->depth = n->depth;
		asttree_addchild_before(n, tmpsubtree);
	}
	while (++i < n->num_child)
	{
		check_if_logical_nodes_need_tmpsubtrees(n->children[i]);
	}
}

// first we join logical nodes between them, 
// then we join the command childs at the right place.
t_asttree	*join_trees_with_parenthesis(t_logicaltree *ltree, \
										t_logicaltree *ctree)
{
	int	i;

	i = 0;
	while (ltree->logicaltree && ltree->logicaltree[i + 1])
	{
		asttree_addchild(ltree->logicaltree[i], ltree->logicaltree[i + 1]);
		i++;
	}
	i = 0;
	while (ltree->logicaltree && ctree->logicaltree && ctree->logicaltree[i])
	{
		join_child_with_parent(ctree->logicaltree[i], ltree->logicaltree);
		i++;
	}
	index_last_logical_node(ltree->logicaltree[0]);
	check_if_logical_nodes_need_tmpsubtrees(ltree->logicaltree[0]);
	if (ltree->logicaltree[0]->depth > 0)
		return (create_subtree(ltree));
	else
		return (ltree->logicaltree[0]);
	return (NULL);
}
