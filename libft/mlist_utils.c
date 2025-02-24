/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:37 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:40 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ptr_lst	*ptrlst_new(void *ptr, int is_critical)
{
	t_ptr_lst	*new;

	new = malloc(sizeof(t_ptr_lst));
	if (!new)
		return (NULL);
	new->is_critical = is_critical;
	new->ptr = ptr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ptrlst_addfront(t_ptr_lst **h, t_ptr_lst *n)
{
	if (!*h)
	{
		*h = n;
		return ;
	}
	n->next = (*h);
	(*h)->prev = n;
	*h = n;
}

void	ptrlst_delone(t_ptr_lst **h, void *ptr)
{
	t_ptr_lst	*b;

	b = *h;
	while (b)
	{
		if (b->ptr == ptr)
		{
			free(b->ptr);
			if (b->prev)
				b->prev->next = b->next;
			if (b->next)
				b->next->prev = b->prev;
			if (b == *h)
				*h = b->next;
			free(b);
			return ;
		}
		b = b->next;
	}
}

void	ptrlst_clear(t_ptr_lst **h, int is_critical)
{
	t_ptr_lst	*t;

	while (*h)
	{
		if ((*h)->is_critical && !is_critical)
		{
			h = &(*h)->next;
			continue ;
		}
		t = (*h)->next;
		free((*h)->ptr);
		free(*h);
		*h = t;
	}
}

int	ptrlst_size(t_ptr_lst *h)
{
	int	size;

	size = 0;
	while (h)
	{
		size++;
		h = h->next;
	}
	return (size);
}
