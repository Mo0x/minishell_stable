/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:39:34 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 18:13:06 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_void(t_asttree *node, t_hash *envp)
{
	int	i;

	i = 0;
	while (i < node->num_child)
	{
		ft_redir_solo(node->children[i], envp);
		i++;
		if (g_signal_status == SIGINT)
			return (130);
	}
	return (0);
}
