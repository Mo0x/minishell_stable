/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:34:06 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 16:34:07 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*hash_getvalue(t_hash *hash, char *key)
{
	t_hash	*tmp;

	tmp = hash;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_hashnode(t_hash *node)
{
	if (node->value)
		wfree(node->value);
	wfree(node->key);
	wfree(node);
}

int	hash_delone(t_hash **head, t_hash *to_del)
{
	t_hash	*tmp;
	t_hash	*prev;
	t_hash	*next;

	tmp = *head;
	next = NULL;
	prev = NULL;
	while (tmp)
	{
		if (tmp->next == to_del)
			prev = tmp;
		if (tmp == to_del)
		{
			if (tmp->next)
				next = tmp->next;
			free_hashnode(to_del);
			if (prev)
				prev->next = next;
			else
				*head = next;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAILURE);
}

t_hash	*get_node_by_key(t_hash	*hash, char *key)
{
	t_hash	*tmp;

	tmp = hash;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	hash_changevalue(t_hash **hash, char *key, char *new_value, int is_critical)
{
	t_hash	*node;

	node = get_node_by_key(*hash, key);
	if (node == NULL)
		return (FAILURE);
	wfree(node->value);
	node->value = ft_strdup(new_value, is_critical);
	if (!node->value)
		error_exit("MALLOC FAILED");
	return (SUCCESS);
}
