/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:48:30 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	get_char_pointer_pointer_malloc_size(char const *s, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			size++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (size + 1);
}

/* i : string à decouper | k : tableau | j : char */

static int	get_segment_size(char const *s, char c, int *index)
{
	int	size;

	size = 0;
	while (s[*index] == c && s[*index])
		(*index)++;
	while (s[*index] != c && s[*index])
	{
		size++;
		(*index)++;
	}
	return (size);
}

static char	**split_motherfuckers(char **splitted, char const *s, \
									char c, int is_critical)
{
	int	i;
	int	j;
	int	k;
	int	size;

	i = 0;
	k = 0;
	while (s[i])
	{
		size = get_segment_size(s, c, &i);
		if (s[i] == '\0' && s[i - 1] == c)
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

char	**ft_split(char const *s, char c, int is_critical)
{
	char	**splitted;
	int		pp_size;

	if (!s)
		return (NULL);
	pp_size = get_char_pointer_pointer_malloc_size(s, c);
	splitted = walloc(pp_size * sizeof(char *), is_critical);
	if (!splitted)
		return (NULL);
	if (!split_motherfuckers(splitted, s, c, is_critical))
	{
		let_it_go(splitted);
		return (NULL);
	}
	return (splitted);
}
