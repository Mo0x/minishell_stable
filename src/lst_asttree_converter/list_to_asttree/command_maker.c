/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:34:23 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:34:24 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list	*cat_command(t_list *lst)
{
	t_list	*new_command;

	new_command = NULL;
	while (lst)
	{
		if (lst->nodetype == LSTCMD || lst->nodetype == LSTCMDARG)
			ft_lstadd_back(&new_command, lstdup(lst));
		lst = lst->next;
	}
	return (new_command);
}

t_list	*get_command_node(t_list *lst)
{
	while (lst)
	{
		if (lst->nodetype == LSTCMD)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	join_command(t_list **lst)
{
	t_list	*tmp;
	t_list	*new_command;
	t_list	*command_node;
	t_list	*tmp2;

	new_command = NULL;
	if (!has_command(*lst))
		return (FAILURE);
	tmp = *lst;
	new_command = cat_command(tmp);
	command_node = get_command_node(tmp);
	while (tmp)
	{
		if (tmp->nodetype == LSTCMDARG)
		{
			tmp2 = tmp->next;
			ft_lstdelone(lst, tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
	*lst = replace_node(*lst, command_node, new_command);
	return (SUCCESS);
}

void	cmd_join(t_list **lst)
{
	if (join_command(lst) == FAILURE)
		return ;
}
