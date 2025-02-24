/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:22 by achatzit          #+#    #+#             */
/*   Updated: 2024/04/30 14:19:01 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	succesive_tokens_failure(t_list	*node)
{
	if (is_redirection(node) && !node->next)
		return (FAILURE);
	if (node && node->next)
	{
		if (node->data_type == INT_TYPE && node->next->data_type == INT_TYPE)
		{
			if ((!is_separating_token(node) && \
				!is_separating_token(node->next)) || \
				(is_redirection(node) && !is_separating_token(node->next)) || \
				(is_redirection(node) && is_redirection(node->next)))
				return (FAILURE);
		}
		if (node->data_type == STR_TYPE && node->next && \
			node->next->data_type == INT_TYPE \
			&& node->next->content.int_val == OPENP)
			return (666);
		if (node->data_type == INT_TYPE && node->content.int_val == CLOSEP \
			&& node->next->data_type == STR_TYPE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	token_missplacement(t_list *lst)
{
	t_list	*tmp;
	int		start;

	start = 0;
	tmp = lst;
	if (is_separating_token(ft_lstlast(lst)) == FAILURE)
		return (error_print("%sToken missplacemnt near unxpctd newline%s\n", \
				BRED, CRESET), FAILURE);
	while (tmp)
	{
		if (start == 0 && is_separating_token(tmp) == FAILURE)
			return (error_print("%sToken missplcmnt near start of prmpt%s\n", \
			BRED, CRESET), FAILURE);
		else if (!succesive_tokens_failure(tmp))
			return (error_print("%sunexpected token near '%s'%s\n", BRED, \
			convert_define_to_str(tmp->content.int_val), CRESET), FAILURE);
		else if (succesive_tokens_failure(tmp) == 666)
			return (error_print("%sunexpected token near '%s'%s\n", BRED, \
		convert_define_to_str(tmp->next->content.int_val), CRESET), FAILURE);
		start = 1;
		tmp = tmp->next;
	}
	return (SUCCESS);
}
