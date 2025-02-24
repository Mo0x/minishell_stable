/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:38:03 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/24 22:38:30 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	b_unset(t_hash *envp, char **param)
{
	t_hash	*node;
	int		i;

	i = 0;
	while (param[i])
	{
		node = get_node_by_key(envp, param[i]);
		if (!node)
		{
			i++;
			continue ;
		}
		hash_delone(&envp, node);
		i++;
	}
	return (0);
}
