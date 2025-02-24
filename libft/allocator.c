/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:37 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:44:18 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

#define HASH_SIZE 8192

unsigned int	hashf(void *p, int size)
{
	unsigned long long	ptr_value;
	unsigned int		hash;
	size_t				i;
	size_t				s;

	ptr_value = (unsigned long long)p;
	i = 0;
	hash = 0;
	s = sizeof(ptr_value);
	while (i < s)
	{
		hash += ((ptr_value >> (i * 8)) & 0xFF);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash % size);
}

void	*allocator_alloc_new(t_ptr_lst *allocs[HASH_SIZE], int size, int crit)
{
	t_ptr_lst	*newnode;
	void		*newalloc;

	newalloc = malloc(size);
	if (!newalloc)
		return (NULL);
	newnode = ptrlst_new(newalloc, crit);
	if (!newnode)
	{
		free(newalloc);
		return (NULL);
	}
	ptrlst_addfront(&allocs[hashf(newalloc, HASH_SIZE)], newnode);
	return (newalloc);
}

void	clear_hash(t_ptr_lst *allocs[HASH_SIZE], int is_critical)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (allocs[i])
			ptrlst_clear(&allocs[i], is_critical);
		i++;
	}
}

void	allocator_print_size(t_ptr_lst *allocs[HASH_SIZE])
{
	int			i;
	int			size;
	t_ptr_lst	*t;

	i = 0;
	size = 0;
	while (i < HASH_SIZE)
	{
		t = allocs[i];
		while (t)
		{
			size += sizeof(t->ptr);
			t = t->next;
		}
		i++;
	}
	printf("allocator size: %d\n", size);
}

void	*allocator(int size, int type, void *ptr, int is_critical)
{
	static t_ptr_lst	*allocs[HASH_SIZE];

	if (type == ALLOC)
		return (allocator_alloc_new(allocs, size, is_critical));
	else if (type == FREE)
		ptrlst_delone(&allocs[hashf(ptr, HASH_SIZE)], ptr);
	else if (type == CLEAR)
		clear_hash(allocs, is_critical);
	else if (type == PRINT_SIZE)
		allocator_print_size(allocs);
	return (NULL);
}
