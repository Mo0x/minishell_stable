/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:53:43 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_doublearray(char **tab)
{
	int	i;

	i = 0;
	while ((tab)[i])
	{
		wfree((tab)[i]);
		(tab)[i] = NULL;
		i++;
	}
	wfree(tab);
}

t_list	*ft_split_lst(char *str, int sep, int is_critical)
{
	int		i;
	char	**spl;
	t_list	*lst;
	t_list	*new_node;

	i = 0;
	spl = ft_split(str, sep, SAFE);
	if (!spl)
		return (NULL);
	lst = NULL;
	while (spl[i])
	{
		new_node = ft_lstnew(spl[i], STR_TYPE, is_critical);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&lst, new_node);
		i++;
	}
	wfree(spl);
	return (lst);
}
