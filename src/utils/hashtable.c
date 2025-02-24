/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:12:21 by achatzit          #+#    #+#             */
/*   Updated: 2024/04/09 14:22:41 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hash	*hashnew(char *key, char *value, int is_critical)
{
	t_hash	*node;

	allocchk(node = walloc(sizeof(t_hash), is_critical));
	if (!node)
		return (NULL);
	node->next = NULL;
	allocchk(node->key = ft_strdup(key, is_critical));
	allocchk(node->value = ft_strdup(value, is_critical));
	if (!node->key || !node->value)
		return (NULL);
	return (node);
}

void	hash_addback(t_hash **hash, t_hash *node)
{
	t_hash	*tmp;

	if (!*hash)
	{
		node->next = *hash;
		*hash = node;
	}
	else
	{
		tmp = *hash;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	hash_size(t_hash *hash)
{
	t_hash	*tmp;
	int		i;

	i = 0;
	tmp = hash;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	hash_clear(t_hash **hash)
{
	t_hash	*tmp;
	t_hash	*tmp2;

	tmp = *hash;
	while (tmp)
	{
		tmp2 = tmp->next;
		wfree(tmp->key);
		wfree(tmp->value);
		wfree(tmp);
		tmp = tmp2;
	}
}
