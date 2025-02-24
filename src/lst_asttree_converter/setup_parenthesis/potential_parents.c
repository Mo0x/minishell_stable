/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_parents.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:41 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:28:49 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_tree_for_missing_childs(t_asttree *node, int *ptr)
{
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	if (node->type == AND_OP || node->type == OR_OP \
			|| node->type == PIPE_OP)
		*ptr += 2 - node->num_child;
	while (++i < node->num_child)
	{
		check_tree_for_missing_childs(node->children[i], ptr);
	}
}

void	get_potential_parents(t_asttree *node, t_potential_parents *pp, \
							int *index, int target_depth)
{
	int	i;

	i = -1;
	if (node == NULL)
		return ;
	if (((node->type == AND_OP || node->type == OR_OP \
		|| node->type == PIPE_OP) && \
		(node->num_child != 2 || \
		has_tmp_subtree(node))) && \
		node->depth == target_depth)
	{
		pp[*index].index = node->index;
		pp[*index].ptr = node;
		if (node->children && node->children[0] && \
			node->children[0]->type == TMP_SUBTREE)
			pp[*index].is_tmp_subtree = 1;
		else
			pp[*index].is_tmp_subtree = 0;
		(*index)++;
	}
	while (++i < node->num_child)
	{
		get_potential_parents(node->children[i], pp, index, target_depth);
	}
}

// dtf = depth to find
// s = array of trees by parenthesis group
t_asttree	**create_potential_parents(t_asttree **s, int dtf)
{
	t_asttree	**pp;
	int			i;
	int			j;

	j = 0;
	i = 0;
	allocchk(pp = walloc((get_pp_array_size(s, dtf) + 1) \
							* sizeof(t_asttree *), SAFE));
	while (s[i])
	{
		if (s[i]->depth == dtf)
		{
			pp[j] = s[i];
			j++;
		}
		i++;
	}
	pp[j] = NULL;
	return (pp);
}

t_potential_parents	*fill_potential_parents(t_asttree **potential_parents, \
											int dtf)
{
	t_potential_parents	*pp;
	int					i;
	int					j;
	int					size;

	i = 0;
	j = 0;
	size = 0;
	while (potential_parents[i++])
		size++;
	i = 0;
	allocchk(pp = walloc((size + 5) * sizeof(t_potential_parents), SAFE));
	while (potential_parents[i])
	{
		get_potential_parents(potential_parents[i], \
								pp, &j, dtf);
		i++;
	}
	pp[j].ptr = NULL;
	return (pp);
}

// we first create an array of pointers to potential parents groups 
// for the orphaned subtree.
// parents must be one depth level below thir child.
// then we check each potential parents for their respective nodes that 
// need childrens
// and finally we pick the closest one.
// c = child (oprhaned subtree), s = array of trees by parenthsis group
// depth_to_find in parameters is here to accomodate the norm
void	join_orphan_subtree_with_parent(t_asttree *c, t_asttree **s, \
										int depth_to_find)
{
	t_index				indx;
	t_asttree			**potential_parents;
	int					distance_to_parent_node;
	t_potential_parents	closest_parent;
	t_potential_parents	*pp;

	setup_join_orphan(&indx, &closest_parent, &distance_to_parent_node);
	depth_to_find = c->depth - 1;
	potential_parents = create_potential_parents(s, depth_to_find);
	pp = fill_potential_parents(potential_parents, depth_to_find);
	while (pp[indx.i].ptr)
	{
		distance_to_parent_node = ft_abs(c->index - pp[indx.i].index);
		if (distance_to_parent_node < closest_parent.index - c->index)
			closest_parent = pp[indx.i];
		indx.i++;
	}
	if (closest_parent.is_tmp_subtree)
		asttree_addchild_before(closest_parent.ptr, c);
	else
		asttree_addchild(closest_parent.ptr, c);
	wfree(pp);
}
