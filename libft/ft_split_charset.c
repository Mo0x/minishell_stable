/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <achatzit@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:48:30 by achatzit          #+#    #+#             */
/*   Updated: 2024/04/28 02:10:53 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static void	let_it_go(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i] != NULL)
	{
		wfree(splitted[i]);
		splitted[i] = NULL;
		i++;
	}
	wfree(splitted);
}

static int	get_char_pointer_pointer_malloc_size(char const *s, char *set)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		while (ft_strchr(set, s[i]) && s[i])
			i++;
		if (!ft_strchr(set, s[i]) && s[i])
		{
			size++;
			while (!ft_strchr(set, s[i]) && s[i])
				i++;
		}
	}
	return (size + 1);
}

/* i : string à decouper | k : tableau | j : char */

static int	get_segment_size(char const *s, char *set, int *index)
{
	int	size;

	size = 0;
	while (ft_strchr(set, s[*index]) && s[*index])
		(*index)++;
	while (!ft_strchr(set, s[*index]) && s[*index])
	{
		size++;
		(*index)++;
	}
	return (size);
}

static char	**split_motherfuckers(char **splitted, char const *s, \
								char *set, int is_critical)
{
	int	i;
	int	j;
	int	k;
	int	size;

	i = 0;
	k = 0;
	while (s[i])
	{
		size = get_segment_size(s, set, &i);
		if (s[i] == '\0' && ft_strchr(set, s[i - 1]))
		{
			splitted[k] = 0;
			return (splitted);
		}
		splitted[k] = walloc((size + 1) * sizeof(char), is_critical);
		if (!splitted[k])
			return (NULL);
		j = -1;
		while (++j < size)
			splitted[k][j] = s[i - size + j];
		splitted[k++][j] = '\0';
	}
	splitted[k] = 0;
	return (splitted);
}

char	**ft_split_charset(char const *s, char *set, int is_critical)
{
	char	**splitted;
	int		pp_size;

	if (!s)
		return (NULL);
	pp_size = get_char_pointer_pointer_malloc_size(s, set);
	splitted = walloc(pp_size * sizeof(char *), is_critical);
	if (!splitted)
		return (NULL);
	if (!split_motherfuckers(splitted, s, set, is_critical))
	{
		let_it_go(splitted);
		return (NULL);
	}
	return (splitted);
}
