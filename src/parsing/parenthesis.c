/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:19:14 by achatzit          #+#    #+#             */
/*   Updated: 2024/04/30 14:19:15 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// nodes containing parenthesis are stored inside an array for easy deletion.
// open parenthesis are stored at even indexes, closing parenthesis are stored
// at odd indexes.
// the pair will be next to eachoter, for example the first opening par
// will be at index 0, and its corresponding closing pair will always be at 
// index 1

static t_list	**get_par_array(t_msh *msh, t_list **lst)
{
	t_list	**par_array;
	t_list	*tmp;
	int		index;
	t_stack	stack;

	allocchk(par_array = walloc((msh->pairs.close_par + \
							msh->pairs.open_par + 1) * sizeof(t_list *), SAFE));
	par_array[msh->pairs.close_par + msh->pairs.open_par] = NULL;
	tmp = *lst;
	index = 1;
	ft_stack_init(&stack);
	while (tmp)
	{
		if (is_token(tmp, OPENP))
			ft_stack_push(&stack, (void *)&tmp, sizeof(&tmp));
		else if (is_token(tmp, CLOSEP))
		{
			par_array[index] = tmp;
			par_array[index - 1] = *((t_list **)ft_stack_pop(&stack));
			index += 2;
		}
		tmp = tmp->next;
	}
	return (par_array);
}

static int	get_index_in_array(t_list **array, t_list *node)
{
	int	i;

	i = 0;
	while ((array)[i])
	{
		if ((array)[i] == node)
			return (i);
		i++;
	}
	return (-1);
}

int	has_only_one_command(t_list *pleft, t_list *pright)
{
	while (pleft != pright)
	{
		if (!is_separating_token(pleft))
		{
			return (FAILURE);
		}
		pleft = pleft->next;
	}
	return (SUCCESS);
}

void	search_and_destroy_useless_parenthesis(t_msh *msh, t_list **lst)
{
	t_list	**par_array;
	int		index;
	t_list	*tmp;
	t_list	*next;

	par_array = get_par_array(msh, lst);
	tmp = *lst;
	while (tmp)
	{
		index = get_index_in_array(par_array, tmp);
		if (index == -1)
			tmp = tmp->next;
		else if (is_token(tmp, CLOSEP) && ((!usefull_tokens(tmp->next) && \
!has_logical_token_before_opening_parenthesis(par_array[index - 1], lst)) || \
			has_only_one_command(par_array[index - 1], par_array[index])))
		{
			next = tmp->next;
			ft_lstdelone(lst, par_array[index - 1]);
			ft_lstdelone(lst, tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	wfree(par_array);
}
