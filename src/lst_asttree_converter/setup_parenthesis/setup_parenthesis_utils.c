/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_parenthesis_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:04 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:30:05 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_parenthesis(t_list *lst)
{
	return (lst && lst->data_type == INT_TYPE && \
			(lst->content.int_val == OPENP || \
			lst->content.int_val == CLOSEP));
}

int	is_end_of_prompt_at_depth_zero(t_list *lst)
{
	return (!is_parenthesis(lst) && lst && !lst->next);
}

int	has_tmp_subtree(t_asttree *node)
{
	return ((node->children && node->children[0] && \
	node->children[0]->type == TMP_SUBTREE));
}

void	index_nodes(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->data_type == INT_TYPE && \
			(lst->content.int_val == OPENP || \
			lst->content.int_val == CLOSEP))
		{
		}
		else
		{
			lst->index = i;
			i++;
		}
		lst = lst->next;
	}
}

void	depth_calculator(t_list *lst)
{
	int	d;

	d = 0;
	while (lst)
	{
		if (lst->data_type == INT_TYPE)
		{
			if (lst->content.int_val == OPENP)
				d++;
			else if (lst->content.int_val == CLOSEP)
				d--;
		}
		lst->depth = d;
		lst = lst->next;
	}
}
