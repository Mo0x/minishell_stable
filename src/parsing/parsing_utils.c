/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:19:34 by achatzit          #+#    #+#             */
/*   Updated: 2024/04/30 14:19:35 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separating_token(t_list *node)
{
	if (node->data_type == INT_TYPE && \
		(node->content.int_val == OR || \
		node->content.int_val == PIPE || \
		node->content.int_val == AND))
		return (FAILURE);
	else
		return (SUCCESS);
}

int	is_redirection(t_list *node)
{
	if (node->data_type == INT_TYPE)
	{
		return (node->content.int_val == LESS || \
				node->content.int_val == DLESS || \
				node->content.int_val == GREAT || \
				node->content.int_val == DGREAT);
	}
	return (0);
}

char	*convert_define_to_str(int define)
{
	if (define == OR)
		return ("||");
	else if (define == PIPE)
		return ("|");
	else if (define == AND)
		return ("&&");
	else if (define == LESS)
		return ("<");
	else if (define == DLESS)
		return ("<<");
	else if (define == GREAT)
		return (">");
	else if (define == DGREAT)
		return (">>");
	else if (define == OPENP)
		return ("(");
	else if (define == CLOSEP)
		return (")");
	return (NULL);
}

int	usefull_tokens(t_list *node)
{
	return (is_token(node, OR) || is_token(node, AND));
}

int	has_logical_token_before_opening_parenthesis(t_list *node, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && tmp->next == node && \
			tmp->data_type == INT_TYPE && \
			(tmp->content.int_val == OR \
			|| tmp->content.int_val == AND))
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}
