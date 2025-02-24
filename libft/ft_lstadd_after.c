/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:53:32 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstadd_after(t_list **lst, t_list *toadd, t_list *position)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		if (tmp == position)
		{
			if (!tmp->next)
			{
				ft_lstadd_back(lst, toadd);
				return (1);
			}
			next = tmp->next;
			tmp->next = toadd;
			toadd->next = next;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
