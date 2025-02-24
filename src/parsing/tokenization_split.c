/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:33 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:46:36 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*cut_remaining_after_token(t_list *node)
{
	char	*new_content;

	allocchk(new_content = ft_substr(node->content.str_val, \
				get_token_len(node->content.str_val), \
				ft_strlen(node->content.str_val) - \
				get_token_len(node->content.str_val), SAFE));
	allocchk((void *)new_content);
	wfree(node->content.str_val);
	node->content.str_val = new_content;
	return (node);
}

static t_list	*create_newnode_with_token(t_list *node)
{
	char	cut_token[3];
	int		inted_token;
	t_list	*new_node;

	ft_strlcpy(cut_token, node->content.str_val, \
			get_token_len(node->content.str_val) + 1);
	inted_token = get_single_token(cut_token);
	allocchk(new_node = ft_lstnew(&inted_token, INT_TYPE, SAFE));
	return (new_node);
}

static t_list	*split_at_token_and_add_nodes(t_list **lst, \
											t_list *node, \
											int pos)
{
	t_list	*new_node;
	char	*cutted_content;
	char	*new_content;
	t_list	*token_node;

	allocchk(cutted_content = ft_substr(node->content.str_val, 0, pos, SAFE));
	allocchk(new_content = ft_substr(node->content.str_val, pos, \
							ft_strlen(node->content.str_val) - pos, SAFE));
	allocchk(new_node = ft_lstnew(new_content, STR_TYPE, SAFE));
	wfree(node->content.str_val);
	node->content.str_val = cutted_content;
	token_node = create_newnode_with_token(new_node);
	cut_remaining_after_token(new_node);
	if (ft_strlen(new_node->content.str_val) == 0)
	{
		ft_lstadd_after(lst, token_node, node);
		return (token_node);
	}
	ft_lstadd_after(lst, token_node, node);
	ft_lstadd_after(lst, new_node, token_node);
	if (ft_strlen(node->content.str_val) == 0)
		ft_lstdelone(lst, node);
	return (token_node);
}

static t_list	*split_inner_tokens(t_list **lst, t_list *node)
{
	int		pos;

	pos = get_token_pos(node->content.str_val);
	if (pos != -1)
		return (split_at_token_and_add_nodes(lst, node, pos));
	else
		return (node);
}

void	split_tokens_inside_strtypes(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->data_type == STR_TYPE && \
			!is_in_quotes(tmp->content.str_val))
		{
			tmp = split_inner_tokens(lst, tmp);
		}
		if (tmp)
		{
			tmp = tmp->next;
		}
	}
}
