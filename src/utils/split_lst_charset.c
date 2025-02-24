/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lst_charset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:07 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 15:16:08 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_split_lst_charset(char *str, char *set, int is_critical)
{
	int		i;
	char	**spl;
	t_list	*lst;
	t_list	*new_node;

	i = 0;
	spl = split_not_in_quotes(str, set, SAFE);
	if (!spl)
		return (NULL);
	lst = NULL;
	while (spl[i])
	{
		allocchk(new_node = ft_lstnew(spl[i], STR_TYPE, is_critical));
		ft_lstadd_back(&lst, new_node);
		i++;
	}
	wfree(spl);
	return (lst);
}
