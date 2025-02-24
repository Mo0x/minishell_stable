/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_split_lst_at_redirection.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:04 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:26:06 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list	*lst_dupe_node(t_list *node)
{
	t_list	*new;

	if (node->data_type == INT_TYPE)
		allocchk(new = ft_lstnew(&node->content.int_val, INT_TYPE, SAFE));
	else if (node->data_type == STR_TYPE)
		allocchk(new = ft_lstnew(node->content.str_val, STR_TYPE, SAFE));
	return (new);
}

t_list	*lst_dupe_n(t_list *lst, int n)
{
	t_list	*new;
	t_list	*prev;
	t_list	*head;

	prev = NULL;
	head = NULL;
	while (n-- && lst)
	{
		new = lstdup(lst);
		if (!prev)
		{
			prev = new;
			head = prev;
		}
		else
		{
			prev->next = new;
			prev = new;
		}
		lst = lst->next;
	}
	return (head);
}

void	add_node_dupeuntil(t_list **prev, t_list **new, t_list **head)
{
	if (!*prev)
	{
		*prev = *new;
		*head = *prev;
	}
	else
	{
		(*prev)->next = *new;
		*prev = *new;
	}
}

t_list	*lst_dupe_until_redirection(t_list *lst)
{
	t_list	*new;
	t_list	*prev;
	t_list	*head;
	int		first_redirect;

	first_redirect = 1;
	prev = NULL;
	head = lst;
	while (lst)
	{
		if (!first_redirect && lst->data_type == INT_TYPE && \
			get_redirect_data(lst->content.int_val))
			return (head);
		first_redirect = 0;
		new = lstdup(lst);
		add_node_dupeuntil(&prev, &new, &head);
		lst = lst->next;
	}
	return (head);
}

// this function creates a simple array of t_list*, containing
// a command (if the prompt is sound), and all its redirections
t_list	**split_lst_at_redirection(t_list **lst, int redirect_nb)
{
	t_list	**splitted;
	int		cmd_tab;
	int		i;
	int		j;

	i = 0;
	allocchk(splitted = walloc((redirect_nb + 5) * sizeof(t_list *), SAFE));
	while (*lst)
	{
		j = 0;
		splitted[i] = lst_dupe_until_redirection(*lst);
		while (j++ < ft_lstsize(splitted[i]))
			*lst = (*lst)->next;
		i++;
	}
	splitted[i] = 0;
	i = 0;
	if (is_void(splitted[0]) && redir_split_has_command(splitted))
	{
		cmd_tab = redir_split_has_command(splitted) - 1;
		splitted[0] = lst_dupe_n(splitted[cmd_tab]->next->next, \
						ft_lstsize(splitted[cmd_tab]->next->next));
		splitted[cmd_tab]->next->next = NULL;
	}
	return (splitted);
}
