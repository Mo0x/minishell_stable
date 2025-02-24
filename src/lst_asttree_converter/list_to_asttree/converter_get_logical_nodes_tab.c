/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_get_logical_nodes_tab.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:45 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:24:47 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	lst_redirects_count(t_list *lst)
{
	int		count;
	t_list	*tmp;

	tmp = lst;
	count = 0;
	while (lst)
	{
		if (lst->data_type == INT_TYPE && \
			get_redirect_data(lst->content.int_val))
			count++;
		lst = lst->next;
	}
	lst = tmp;
	return (count);
}

int	get_number_of_inttypes_nonredirect_tokens(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		if (is_int_but_not_redirect(lst))
			size++;
		lst = lst->next;
	}
	return (size);
}

t_logicaltree	*get_logical_nodes_tab(t_list *lst, int size, int i)
{
	t_logicaltree	*tree;
	t_asttree		**tab;

	tab = NULL;
	size = get_number_of_inttypes_nonredirect_tokens(lst);
	if (size > 0)
	{
		allocchk(tab = walloc((size + 1) * sizeof(t_asttree *), SAFE));
		while (lst)
		{
			if (is_int_but_not_redirect(lst))
			{
				tab[i] = \
				asttree_create_node(convert_token_num((lst)->content.int_val), \
				NULL, NULL);
				tab[i]->index = lst->index;
				tab[i]->depth = lst->depth;
				i++;
			}
			lst = lst->next;
		}
		tab[i] = NULL;
	}
	return (allocchk(tree = walloc(sizeof(t_logicaltree), SAFE)), \
	tree->size = size, tree->logicaltree = tab, tree);
}
