/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:13 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/24 22:12:32 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_nodetype	convert_token_num(int token)
{
	if (token == PIPE)
		return (PIPE_OP);
	if (token == AND)
		return (AND_OP);
	if (token == OR)
		return (OR_OP);
	if (token >= 3 && token <= 6)
		return (REDIRECTION);
	if (token == VOIDT)
		return (VOID);
	return (ERROR);
}

char	*get_redirect_data(int token)
{
	if (token == 3)
		return ("<");
	else if (token == 4)
		return (">");
	else if (token == 5)
		return ("<<");
	else if (token == 6)
		return (">>");
	return (NULL);
}

t_nodetype	is_builtin(char *s)
{
	if (!ft_strcmp(s, "unset") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd") \
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "exit") || \
		!ft_strcmp(s, "env") || !ft_strcmp(s, "echo"))
		return (BUILTIN);
	else
		return (COMMAND);
}

int	is_int_but_not_redirect(t_list *lst)
{
	return (lst->data_type == INT_TYPE && \
		!get_redirect_data(lst->content.int_val));
}

t_asttree	*create_subtree(t_logicaltree *ltree)
{
	t_asttree	*subtree;

	subtree = asttree_create_node(SUBTREE, NULL, NULL);
	subtree->index = ltree->logicaltree[0]->index;
	subtree->depth = ltree->logicaltree[0]->depth;
	asttree_addchild(subtree, ltree->logicaltree[0]);
	return (subtree);
}
