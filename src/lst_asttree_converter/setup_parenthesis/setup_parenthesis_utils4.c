/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_parenthesis_utils4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:31 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:30:32 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// this function creates and returns a new t_list* with every t_list*
// from the same parenthesis group.
t_list	*join_parenthesis_group(int group, t_par_depthsplit **p)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	while (p[i])
	{
		if (p[i]->lst->par_group_index == group)
		{
			ft_lstadd_back(&tmp, whole_lstdup(p[i]->lst));
		}
		i++;
	}
	return (tmp);
}

t_asttree	*join_subtrees(t_asttree **s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i]->type == SUBTREE)
		{
			join_orphan_subtree_with_parent(s[i], s, 0);
		}
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i]->depth == 0)
			return (s[i]);
	}
	return (NULL);
}
