/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_parenthesis_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:24 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:30:25 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_orphaned_trees_nb(t_asttree **s)
{
	int	i;
	int	orphans;

	i = 0;
	orphans = 0;
	while (s[i])
	{
		if (s[i]->type == SUBTREE)
			orphans++;
		i++;
	}
	return (orphans);
}

void	setup_join_orphan(t_index *i, \
						t_potential_parents *clst, \
						int *dist)
{
	i->i = 0;
	i->j = 0;
	clst->ptr = NULL;
	clst->index = INT_MAX;
	*dist = 0;
}

int	get_pp_array_size(t_asttree **s, int dtf)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i]->depth == dtf)
			size++;
		i++;
	}
	return (size);
}

t_list	*find_first_lst_for_group(int group, t_par_depthsplit **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i]->lst->par_group_index == group)
			return (p[i]->lst);
		i++;
	}
	return (NULL);
}

int	get_highest_par_group_index(t_par_depthsplit **p)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	while (p[i])
	{
		if (ret < p[i]->lst->par_group_index)
			ret = p[i]->lst->par_group_index;
		i++;
	}
	return (ret);
}
