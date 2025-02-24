/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:17:21 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 15:17:22 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_stack_init(t_stack *stack)
{
	stack->top = NULL;
}

void	ft_stack_push(t_stack *stack, void *data, size_t size)
{
	t_stack_node	*new_node;
	void			*new_data;

	allocchk(new_node = (t_stack_node *)walloc(sizeof(t_stack_node), SAFE));
	allocchk(new_data = walloc(size, SAFE));
	ft_memcpy(new_data, data, size);
	new_node->data = new_data;
	new_node->next = stack->top;
	stack->top = new_node;
}

void	*ft_stack_pop(t_stack *stack)
{
	t_stack_node	*temp;
	void			*data;

	if (stack->top == NULL)
		return (NULL);
	temp = stack->top;
	data = temp->data;
	stack->top = stack->top->next;
	wfree(temp);
	return (data);
}

void	*ft_stack_peek(t_stack *stack)
{
	return (stack->top->data);
}
