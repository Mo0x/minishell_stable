/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_join_child_with_parents.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:25:03 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:03 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// this function checks if a command asttree node is destined to be
// a child of a given logical asttree node. It first goes all the way to the end
// of the lparam lst to check if the logical node is adgacent to the right,
// then checks if the logical node is directly adjacent to the left of the first
// lst node.
int	is_cmd_a_child(t_asttree *lnode, t_asttree *cnode)
{
	t_list	*tmp;

	tmp = cnode->l_param;
	if (tmp->index - 1 == lnode->index)
		return (1);
	while (tmp && tmp->next && tmp->next->data_type == STR_TYPE)
		tmp = tmp->next;
	return (tmp->index + 1 == lnode->index || \
			tmp->index - 1 == lnode->index);
}

// if a command node has redirection childrens it needs to go to the last
// one's lparam, check its last node index;
// otherwise just check its own lparam;
int	get_index_of_last_node_in_the_command(t_asttree *n)
{
	int		i;
	t_list	*t;

	i = n->num_child;
	if (i)
	{
		t = n->children[i - 1]->l_param;
		while (t->next)
			t = t->next;
		return (t->index);
	}
	else
	{
		t = n->l_param;
		while (t->next)
			t = t->next;
		return (t->index);
	}
}

int	find_parent_at_the_right_of_child(t_asttree *c, t_asttree **p, int i)
{
	if (get_index_of_last_node_in_the_command(c) + 1 == p[i]->index)
	{
		if (p[i]->children && p[i]->children[0] && \
		(p[i]->children[0]->type == OR_OP || \
		p[i]->children[0]->type == AND_OP || \
		p[i]->children[0]->type == PIPE_OP))
			asttree_addchild_before(p[i], c);
		else
			asttree_addchild(p[i], c);
		return (1);
	}
	return (0);
}

int	find_parent_at_the_left_of_child(t_asttree *c, t_asttree **p, int i)
{
	t_asttree	*tmpsubtree;

	if (c->l_param->index - 1 == p[i]->index)
	{
		asttree_addchild(p[i], c);
		if (p[i]->children[0] == c)
		{
			tmpsubtree = asttree_create_node(TMP_SUBTREE, NULL, NULL);
			tmpsubtree->index = 0;
			tmpsubtree->depth = p[i]->depth;
			asttree_addchild_before(p[i], tmpsubtree);
		}
		return (1);
	}
	return (0);
}

// the logic first checks if it can find a parent 
// when looking at the right of the child,
// and if not it checks at its left. usually a prent will be at the right
// of its children and only have one command as child, but in the case 
// of the last logical node of a prompt (or a subtree), that last node can have
// 2 command childrens.
void	join_child_with_parent(t_asttree *c, t_asttree **p)
{
	int			i;

	i = 0;
	while (p[i])
	{
		if (find_parent_at_the_right_of_child(c, p, i))
			return ;
		i++;
	}
	i = 0;
	while (p[i])
	{
		if (find_parent_at_the_left_of_child(c, p, i))
			return ;
		i++;
	}
}
