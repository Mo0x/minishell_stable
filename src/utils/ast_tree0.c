/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:04:03 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 16:16:31 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_asttree	*asttree_create_node(t_nodetype type, char *data, char **param)
{
	t_asttree	*new;

	allocchk(new = walloc(sizeof(t_asttree), SAFE));
	if (data)
		new->value = ft_strdup(data, SAFE);
	else
		new->value = NULL;
	new->l_param = NULL;
	new->type = type;
	new->children = NULL;
	new->param = param;
	new->num_child = 0;
	new->pid = 0;
	new->to_close = 0;
	new->fdi = STDIN_FILENO;
	new->fdo = STDOUT_FILENO;
	new->parent = NULL;
	new->skip = 0;
	new->here_doc = NULL;
	new->lst = 0;
	new->is_last_logical_node = 0;
	new->stached_heredoc = NULL;
	return (new);
}
