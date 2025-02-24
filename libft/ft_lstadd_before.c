/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:44:46 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:44:48 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_before(t_list **lst, t_list *target, t_list *new)
{
	t_list	*tmp;
	t_list	*prev;

	if (target == *lst)
		return (ft_lstadd_front(lst, new));
	tmp = (*lst)->next;
	prev = *lst;
	while (tmp)
	{
		if (tmp == target)
		{
			prev->next = new;
			new->next = target;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
