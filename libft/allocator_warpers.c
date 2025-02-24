/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_warpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:45:18 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:45:37 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*walloc(int size, int is_critical)
{
	return (allocator(size, ALLOC, NULL, is_critical));
}

void	wfree(void *ptr)
{
	allocator(0, FREE, ptr, 0);
}

void	wclear(int free_critical)
{
	if (free_critical == 1)
		allocator(0, CLEAR, NULL, CRITICAL);
	else
		allocator(0, CLEAR, NULL, SAFE);
}
