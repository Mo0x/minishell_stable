/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:35:39 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:35:41 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, t_list *node_to_delete)
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !*lst || !node_to_delete)
		return ;
	if (*lst == node_to_delete)
	{
		temp = *lst;
		*lst = (*lst)->next;
		wfree(temp);
		return ;
	}
	current = *lst;
	while (current->next && current->next != node_to_delete)
		current = current->next;
	if (current->next == node_to_delete)
	{
		temp = current->next;
		current->next = current->next->next;
		wfree(temp);
	}
}
