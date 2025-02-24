/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodetype_flagger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:34:15 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:34:18 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	has_command(t_list *lst)
{
	while (lst)
	{
		if (lst->nodetype == LSTCMD)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	is_void(t_list *node)
{
	static char	voidness[] = {-6, -6, -6, 0};

	if (node->data_type == STR_TYPE)
		return (!ft_strcmp(node->content.str_val, voidness));
	return (0);
}

void	init_lst_nodetypes(t_list *lst)
{
	while (lst)
	{
		lst->nodetype = LSTEMPTY;
		lst = lst->next;
	}
}

void	flag_lstnodes(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	init_lst_nodetypes(lst);
	while (tmp)
	{
		if (is_void(tmp))
		{
			tmp->nodetype = LSTVOID;
			tmp = tmp->next;
		}
		if (is_redirection(tmp) && tmp->nodetype == LSTEMPTY)
		{
			tmp->nodetype = LSTREDIR;
			if (tmp->next && tmp->content.int_val != DLESS)
				tmp->next->nodetype = LSTFILE;
			else if (tmp->next && tmp->content.int_val == DLESS)
				tmp->next->nodetype = LSTLIMITER;
		}
		else if (!has_command(lst) && tmp->nodetype == LSTEMPTY)
			tmp->nodetype = LSTCMD;
		else if (tmp->nodetype == LSTEMPTY)
			tmp->nodetype = LSTCMDARG;
		tmp = tmp->next;
	}
}
