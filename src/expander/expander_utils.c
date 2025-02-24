/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:47:30 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:47:31 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->data_type == STR_TYPE)
		{
			if ((*lst)->content.str_val)
				wfree((*lst)->content.str_val);
		}
		wfree((*lst));
		*lst = tmp;
	}
	*lst = NULL;
}

void	putback_dollars(t_list *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		if (lst->data_type == STR_TYPE)
		{
			while (lst->content.str_val[i])
			{
				if (lst->content.str_val[i] == 2)
					lst->content.str_val[i] = '$';
				i++;
			}
		}
		lst = lst->next;
	}
}

void	get_heredoc_next(t_list *lst)
{
	while (lst)
	{
		if (lst->data_type == INT_TYPE && lst->content.int_val == DLESS \
			&& lst->next)
			lst->next->is_heredoc_next = 1;
		lst = lst->next;
	}
}

void	setup_quotes_charset(char *s, char *set)
{
	int	cur_quote;

	cur_quote = 0;
	while (*s)
	{
		if (!cur_quote && (*s == 34 || *s == 39))
			cur_quote = *s;
		else if (cur_quote && *s == cur_quote)
			cur_quote = 0;
		else if (cur_quote && ft_strchr(set, *s))
			*s = 1;
		s++;
	}
}
