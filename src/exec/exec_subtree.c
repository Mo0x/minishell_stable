/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:05:25 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:48:52 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*echo lol && (asdfasdf && asdfasdf) || echo success*/

#include "../../includes/minishell.h"

int	ft_exec_subtree(t_asttree *node, t_hash *envp)
{
	int	ret;

	ret = 0;
	if (node->type == SUBTREE)
		node->skip = 1;
	ret = ft_exec(node->children[0], envp);
	return (ret);
}
