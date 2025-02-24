/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:26:08 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:34:09 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_am_i_env(char *value, t_hash *envp)
{
	while (envp)
	{
		printf("key = %s value = %s\n", envp->key, value + 1);
		if (!(ft_strcmp(envp->key, value + 1)))
			return (1);
		envp = envp->next;
	}
	return (0);
}

void	ft_param_expander1(t_asttree *node, t_hash *envp)
{
	while (envp)
	{
		if (!(ft_strcmp(envp->key, node->value + 1)))
		{
			expander(&(node->l_param), envp);
			break ;
		}
		envp = envp->next;
	}
}

void	ft_param_expander(t_asttree *node, t_hash *envp)
{
	int		max;
	int		i;
	t_list	*list;

	if (node->value[0] == '$')
		ft_param_expander1(node, envp);
	else
		expander(&(node->l_param), envp);
	if (node->l_param && node->l_param->data_type == STR_TYPE)
	{
		list = node->l_param;
		max = ft_count_param_list(node->l_param) + 1;
		node->param = walloc(sizeof(char *) * max, SAFE);
		i = -1;
		while (list)
		{
			node->param[++i] = list->content.str_val;
			list = list->next;
		}
		i++;
		node->param[i] = NULL;
	}
	if (node->param)
		node->value = node->param[0];
}

/*void	ft_param_expander_init(t_asttree *node)
{
	asttree_preorder(node, ft_param_expander);
}*/
