/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:52:27 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/30 20:56:07 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_heredocv3(t_asttree *node, t_hash *envp)
{
	if (node->type == REDIRECTION)
	{
		if (!(ft_strcmp(node->value, "<<")))
		{
			if (node->l_param)
				ft_param_expander(node, envp);
			node->parent->stached_heredoc = ft_heredoc_pipe(node->param[1],
					envp);
			if (!node->parent->stached_heredoc)
				return (130);
		}
	}
	return (0);
}

int	ft_exec_heredoc(t_asttree *node, t_hash *envp)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	if (node == NULL)
		return (-1);
	flag = ft_heredocv3(node, envp);
	if (flag)
		return (flag);
	while (++i < node->num_child)
	{
		if (flag)
			break ;
		flag = ft_exec_heredoc(node->children[i], envp);
	}
	return (flag);
}
