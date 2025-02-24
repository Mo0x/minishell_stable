/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:21:12 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:21:13 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	word_split(t_list **lst)
{
	t_list	*newlist;
	t_list	*new;
	t_list	**old_head_ptr;

	old_head_ptr = lst;
	newlist = NULL;
	while (*lst)
	{
		if ((*lst)->data_type == INT_TYPE)
			ft_lstadd_back(&newlist, lstdup(*lst));
		else
		{
			allocchk((*lst)->content.str_val = \
				ft_strtrim((*lst)->content.str_val, " \t", SAFE));
			new = ft_split_lst_charset((*lst)->content.str_val, " \t", SAFE);
			ft_lstadd_back(&newlist, new);
		}
		*lst = (*lst)->next;
	}
	free_lst(old_head_ptr);
	*lst = newlist;
}
