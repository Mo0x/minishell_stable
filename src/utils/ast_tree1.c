/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:56 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 16:39:14 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	asttree_addchild(t_asttree *parent, t_asttree *child)
{
	t_asttree	**new_children;
	int			i;

	if (parent == NULL || child == NULL)
		ft_eq("Fatal error asttree addchild");
	parent->num_child++;
	allocchk(new_children = (t_asttree **)walloc(parent->num_child
			* sizeof(t_asttree *), SAFE));
	i = -1;
	while (++i < parent->num_child - 1)
		new_children[i] = (t_asttree *)parent->children[i];
	new_children[parent->num_child - 1] = child;
	wfree(parent->children);
	parent->children = (struct s_asttree **)new_children;
	child->parent = parent;
}

void	asttree_addchild_before(t_asttree *parent, t_asttree *child)
{
	t_asttree	**new_children;
	int			i;
	int			j;

	if (parent == NULL || child == NULL)
		ft_eq("Fatal error asttree addchild_before");
	parent->num_child++;
	allocchk(new_children = (t_asttree **)walloc(parent->num_child
			* sizeof(t_asttree *), SAFE));
	if (!new_children)
		ft_eq("Fatal error asttree addchild_before");
	i = parent->num_child;
	j = 0;
	while (--i > 0)
		new_children[i] = (t_asttree *)parent->children[j++];
	new_children[0] = child;
	wfree(parent->children);
	parent->children = (struct s_asttree **)new_children;
	if (parent->num_child == 3 && parent->children[2])
	{
		asttree_delete_node(parent->children[2]);
		parent->num_child--;
	}
	child->parent = parent;
}

void	asttree_delete_node(t_asttree *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < node->num_child)
		asttree_delete_node((t_asttree *)node->children[i++]);
	wfree(node->value);
	wfree(node->children);
	if (node->param)
		ft_freetab((void **)node->param);
	wfree(node);
	node = NULL;
}

/*pre order*/
void	asttree_preorder(t_asttree *node, void (*f)(t_asttree *))
{
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	f(node);
	while (++i < node->num_child)
		asttree_preorder(node->children[i], f);
}

/*post order probably the one we'll use,
		A
	/ \
   B   C
  / \
 D   E
		Pre-order traversal: A -> B -> D -> E -> C
	Post-order traversal: D -> E -> B -> C -> A
*/
void	asttree_postorder(t_asttree *node, void (*f)(t_asttree *))
{
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	while (++i < node->num_child)
		asttree_postorder(node->children[i], f);
	f(node);
}
