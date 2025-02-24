/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_var_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:58:43 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 15:58:45 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cleanup_empty_var(t_list **head, t_list **lst)
{
	t_list	*tmp;

	if (*lst == *head && !(*lst)->next)
	{
		ft_lstdelone(head, *lst);
		lst = NULL;
		*head = NULL;
	}
	else if (!(*lst)->next)
	{
		ft_lstdelone(head, *lst);
		*lst = NULL;
	}
	else
	{
		tmp = (*lst)->next;
		ft_lstdelone(head, *lst);
		*lst = tmp;
		return (1);
	}
	return (0);
}
