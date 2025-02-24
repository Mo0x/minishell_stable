/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:55 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 16:33:57 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hash	*ft_dup_hash(t_hash *src)
{
	t_hash	*head;
	t_hash	*ret;
	t_hash	*tmp;

	ret = NULL;
	while (src)
	{
		if (!ret)
		{
			ret = hashnew(src->key, src->value, SAFE);
			head = ret;
		}
		else
		{
			tmp = hashnew(src->key, src->value, SAFE);
			ret->next = tmp;
			ret = ret->next;
		}
		src = src->next;
	}
	if (ret)
		ret->next = NULL;
	return (head);
}

void	init_sort_hash_struct(t_sort_hash *sh, t_hash *envp)
{
	sh->sorted = NULL;
	sh->current = NULL;
	sh->next = NULL;
	sh->ret = ft_dup_hash(envp);
}

t_hash	*ft_sort_hash_export(t_hash *envp)
{
	t_sort_hash	sh;

	init_sort_hash_struct(&sh, envp);
	while (sh.ret != NULL)
	{
		sh.next = sh.ret->next;
		if (sh.sorted == NULL || ft_strcmp(sh.ret->key, sh.sorted->key) < 0)
		{
			sh.ret->next = sh.sorted;
			sh.sorted = sh.ret;
		}
		else
		{
			sh.current = sh.sorted;
			while (sh.current->next != NULL && \
					ft_strcmp(sh.ret->key, sh.current->next->key) >= 0)
				sh.current = sh.current->next;
			sh.ret->next = sh.current->next;
			sh.current->next = sh.ret;
		}
		sh.ret = sh.next;
	}
	return (sh.sorted);
}

/*TODO with write to check returns*/
void	print_hashlist(t_hash *hash)
{
	while (hash)
	{
		printf("declare -x %s=\"%s\"\n", hash->key, hash->value);
		hash = hash->next;
	}
}
