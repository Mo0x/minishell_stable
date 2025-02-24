/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:20:44 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 14:20:45 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// wildcards are not epxpanded if inside any quote.
// they also are expanded after the quotes
// lol
// ca va etre chiant
// echo *.c  -> expands
// echo "*".c -> outputs *.c
// echo *."c" || *'.'c -> expands
// echo $SHLVL *.c -> outputs 1*.c
void	replace_wildcard_with_1ascii_forfiles(char **s)
{
	int	i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '*')
			(*s)[i] = 1;
		i++;
	}
}

void	free_file_list(char ***fl)
{
	int	i;

	i = 0;
	while ((*fl)[i])
		wfree((*fl)[i++]);
	wfree(*fl);
}

void	replace_1ascii_with_wildcard(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while ((*tab) && (*tab)[i])
	{
		j = 0;
		while ((*tab)[i][j])
		{
			if ((*tab)[i][j] == 1)
			{
				(*tab)[i][j] = '*';
			}
			j++;
		}
		i++;
	}
}

void	replace_1_with_wild_single(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == 1)
			(*str)[i] = '*';
		i++;
	}
}

int	get_file_list_len(t_list *lst)
{
	char	**file_list;
	int		i;

	file_list = look_for_wildcards(lst->content.str_val);
	if (!file_list)
		return (0);
	i = 0;
	while (file_list[i])
		i++;
	return (i);
}
