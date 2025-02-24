/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:35:44 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:35:45 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*replace_node(t_list *head, t_list *to_replace, t_list *new_node)
{
	t_list	*current;
	t_list	*last_new_node;

	if (!head || !to_replace || !new_node)
		return (head);
	if (head == to_replace)
	{
		last_new_node = new_node;
		while (last_new_node->next)
			last_new_node = last_new_node->next;
		last_new_node->next = head->next;
		return (new_node);
	}
	current = head;
	while (current->next && current->next != to_replace)
		current = current->next;
	if (current->next == to_replace)
	{
		last_new_node = new_node;
		while (last_new_node->next)
			last_new_node = last_new_node->next;
		last_new_node->next = to_replace->next;
		current->next = new_node;
	}
	return (head);
}
