/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:45:23 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int type, int is_critical)
{
	t_list	*node;

	node = walloc(1 * sizeof(t_list), is_critical);
	if (!node)
		return (NULL);
	if (type == INT_TYPE)
	{
		node->content.int_val = *((int *)content);
		node->data_type = INT_TYPE;
	}
	else if (type == STR_TYPE)
	{
		node->content.str_val = (char *)content;
		node->data_type = STR_TYPE;
	}
	node->is_heredoc_next = 0;
	node->index = -1;
	node->depth = -1;
	node->next = NULL;
	return (node);
}
