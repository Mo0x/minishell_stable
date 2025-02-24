/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:29:41 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:29:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <limits.h>
#include <threads.h>
#include <unistd.h>

// This file includes the logic to handle prompts with useful parenthesis.
// they are used for priorities when using logical operators, and maybe
// concatenate the outputs into a single buffer when piping.
// the logic is decorticated as follows :
//
// -we take the lst containing the tokens from the parser.
// we index_nodes() from 0 to n, following a left to right order.
// parenthesis are not indexed and are skipped.
// -then we depth_calculator(), to give each token their respective 
// parenthesis depth at which they appear in the prompt.
// -then we get_groups_parenthesis_index() to give each token their 
// respective parenthesis group index (see the function for more detail).
// -we create the pardsplit array of linked lists, useless little bastard, 
// where we parse the tokens left to right and split at each depth change
// -then we create the groupjoin array of linked lists, much more usefull,
// where we join every tokens that share a same parenthesis group.
// -we convert these arrays of linked lists to arrays of AST, they are still
// split by depth. the nodes are joined together already, so we get small
// incomplete ASTs.
// -we add subtree nodes to the root of each AST where depth > 0
// -finally we join all these trees together following a simple rule :
// a subtree node will always be linked to the parent looking for a child
// with the closest index. A few tricks have been used at this step :
// --since we cannot know at small-tree-linkage step whether a child needs to
// be at the right or the left of a parent, we first do a check to the left and
// then a check to the right to find the parent.
// if in the look-left step there is only one child after adding it, 
// then that child needs to be at the right and a tmp subtree child is 
// added at its left.
// we could implement a version that compares to the original lst and avoid
// further time complexity, but the loss of real time and added logic complexity
// is not worth it considering the size of prompts 
// will surely never attain sizes
// that would make the matter embarassing.
// --a few small edge cases i havent taken time 
// to understand resulting from out of bound
// array accessing have been resolved by timely returns and checks. 
// if upon further development
// there are unitiliazed access on certain checks, 
// look for tmp subtrees or subtrees nodes,
// they have not been propely initialized like the other nodes. 
// Not a problem at this point, 
// but something to keep in mind.
// --also there are 2 arrays to modify at some point in the 
// join_orphan_subtree_with_parent
// function, the 100000 stack allocated one and the 100000 heap allocated one. 
// There need
// to be a proper size to allocate.
// mettre les ft_stack dans la libft

// this function fills the par_group_index in the lst, 
// which represents the parenthesis 
// group the token is in. for example in this list :
// 1 2 (3 4 (5) 6 7) 8 (9 10 (11) 12 (13) 14)
// the tokens are in these groups :
// group 0 : 1 2 8
// group 1 : 3 4 6 7
// group 2 : 5
// group 3 : 9 10 12 14
// group 4 : 11
// group 5 : 13
void	get_groups_parenthesis_index(t_list *lst)
{
	t_stack	stack;
	int		groups_track;
	int		tmp;

	groups_track = 0;
	ft_stack_init(&stack);
	tmp = groups_track;
	ft_stack_push(&stack, (void *)&tmp, sizeof(int));
	while (lst)
	{
		if (is_parenthesis(lst) && lst->content.int_val == OPENP)
		{
			groups_track++;
			tmp = groups_track;
			ft_stack_push(&stack, (void *)&tmp, sizeof(int));
		}
		else if (is_parenthesis(lst) && lst->content.int_val == CLOSEP)
			ft_stack_pop(&stack);
		else
			lst->par_group_index = *((int *)ft_stack_peek(&stack));
		if (lst)
			lst = lst->next;
	}
}

// the conversion from lst to pardsplit is avoidable by directly
// converting the lst into groups, using the groupjoin variable
// but for whatever reson doing so will trigger UB because of
// uninitalilzed variables (the par_index_group in lst)
// but going with this first useless conversion does not soooo....... 
// i int the parameters is here for the norm.
void	split_at_parenthese(t_par_depthsplit **pardsplit, t_list *lst, int i)
{
	t_list				*newhead;
	int					start_newlst;

	start_newlst = 1;
	newhead = NULL;
	while (lst)
	{
		skip_parenthesis_and_put_starnewlst_at_1_if_so(&lst, &start_newlst);
		if (lst && start_newlst)
			newhead = dup_lst_and_put_newlst_at_0(lst, &start_newlst);
		else if (lst)
			ft_lstadd_back(&newhead, lstdup(lst));
		if ((lst && lst->next && is_parenthesis(lst->next)) || \
			(is_end_of_prompt_at_depth_zero(lst)))
		{
			allocchk(pardsplit[i] = walloc(sizeof(t_par_depthsplit), SAFE));
			pardsplit[i]->lst = newhead;
			pardsplit[i]->depth = newhead->depth;
			i++;
		}
		if (lst)
			lst = lst->next;
	}
	pardsplit[i] = NULL;
}

// this function takes the useless par_depthsplit and creates a new one,
// where each level of the array is a level of parenthesis.
t_par_depthsplit	**join_parenthis_split_by_group(t_par_depthsplit **p)
{
	t_par_depthsplit	**ret;
	int					i;

	allocchk(ret = walloc((get_highest_par_group_index(p) + 2) * \
						sizeof(t_par_depthsplit *), SAFE));
	i = 0;
	while (i <= get_highest_par_group_index(p))
	{
		allocchk(ret[i] = walloc(sizeof(t_par_depthsplit), SAFE));
		ret[i]->lst = join_parenthesis_group(i, p);
		ret[i]->depth = ret[i]->lst->depth;
		ret[i]->parindex = ret[i]->lst->par_group_index;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

// this function takes the lst grouped by parenthesis and
// outputs an array of asttree* grouped by parenthesis level.
t_asttree	**convert_lstpargroup_to_asttree(t_par_depthsplit **p)
{
	t_asttree	**ret;
	int			size;
	int			i;

	size = 0;
	while (p[size])
		size++;
	allocchk(ret = walloc((size + 1) * sizeof(t_asttree *), SAFE));
	i = 0;
	while (i < size)
	{
		ret[i] = convert_list_to_asttree(NULL, &p[i]->lst, 1);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

t_asttree	*setup_parenthesis_stuff(t_list **lst)
{
	t_par_depthsplit	**pardsplit;
	t_par_depthsplit	**groupjoin;
	t_asttree			**tree_pargroup_split;
	t_asttree			*final_tree;

	index_nodes(*lst);
	depth_calculator(*lst);
	get_groups_parenthesis_index(*lst);
	allocchk(pardsplit = walloc((get_parsplit_count(*lst) + 2) * \
							sizeof(t_par_depthsplit *), SAFE));
	split_at_parenthese(pardsplit, *lst, 0);
	groupjoin = join_parenthis_split_by_group(pardsplit);
	if (DEBUG)
		print_par_infos(groupjoin);
	tree_pargroup_split = convert_lstpargroup_to_asttree(groupjoin);
	final_tree = join_subtrees(tree_pargroup_split);
	return (final_tree);
}
