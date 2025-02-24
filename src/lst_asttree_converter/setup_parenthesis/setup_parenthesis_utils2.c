/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_parenthesis_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:12 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:30:13 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_parsplit_count(t_list *lst)
{
	int	count;
	int	last_depth;

	count = 1;
	last_depth = lst->depth;
	while (lst)
	{
		if (lst->data_type == INT_TYPE && \
			(lst->content.int_val == OPENP || \
			lst->content.int_val == CLOSEP))
		{
		}
		else
		{
			last_depth = lst->depth;
		}
		if (lst->depth != last_depth)
			count++;
		lst = lst->next;
	}
	return (count);
}

// a mettre ailleurs
t_list	*lstdup(t_list *lst)
{
	t_list	*new;

	allocchk(new = walloc(sizeof(t_list), SAFE));
	if (lst->data_type == INT_TYPE)
	{
		new->data_type = INT_TYPE;
		new->content.int_val = lst->content.int_val;
	}
	else
	{
		new->data_type = STR_TYPE;
		allocchk(new->content.str_val = ft_strdup(lst->content.str_val, SAFE));
	}
	new->depth = lst->depth;
	new->index = lst->index;
	new->is_bridge = lst->is_bridge;
	new->is_heredoc_next = lst->is_heredoc_next;
	new->par_group_index = lst->par_group_index;
	new->nodetype = lst->nodetype;
	new->next = NULL;
	return (new);
}

t_list	*whole_lstdup(t_list *lst)
{
	t_list	*new;
	t_list	*tmp;

	new = lstdup(lst);
	lst = lst->next;
	while (lst)
	{
		tmp = lstdup(lst);
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}

void	skip_parenthesis_and_put_starnewlst_at_1_if_so(t_list **lst, int *snlst)
{
	while (is_parenthesis(*lst))
	{
		*lst = (*lst)->next;
		*snlst = 1;
	}
}

t_list	*dup_lst_and_put_newlst_at_0(t_list *lst, int *snlst)
{
	t_list	*newhead;

	newhead = lstdup(lst);
	*snlst = 0;
	return (newhead);
}
