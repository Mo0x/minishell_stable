/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_join_no_parenthesis.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:25:40 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:25:42 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_asttree	*join_trees_no_parenthesis(t_logicaltree *ltree, \
										t_logicaltree *ctree)
{
	int	i;

	i = 0;
	while (ltree->logicaltree && ltree->logicaltree[i] && ctree->logicaltree[i])
	{
		asttree_addchild(ltree->logicaltree[i], ctree->logicaltree[i]);
		i++;
	}
	i = 0;
	while (ltree->logicaltree && ltree->logicaltree[i + 1])
	{
		asttree_addchild(ltree->logicaltree[i], ltree->logicaltree[i + 1]);
		i++;
	}
	if (ltree->size > 0)
		asttree_addchild(ltree->logicaltree[i], ctree->logicaltree[i + 1]);
	if (ltree->logicaltree && ltree->logicaltree[0])
		return (ltree->logicaltree[0]);
	else
		return (ctree->logicaltree[0]);
}
