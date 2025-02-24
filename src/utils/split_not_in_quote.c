/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_not_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:18 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 15:16:19 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_one_char(char *s, char c)
{
	char	*new;
	char	ch[2];

	allocchk(new = walloc(ft_strlen(s) + 2, SAFE));
	new[0] = 0;
	ch[0] = c;
	ch[1] = 0;
	ft_strcpy(new, s);
	ft_strncat(new, ch, 1);
	wfree(s);
	return (new);
}

int	pp_size(char *s, char *set)
{
	int	size;

	size = 0;
	while (*s)
	{
		if (ft_strchr(set, *s))
			size++;
		s++;
	}
	return (size + 5);
}

char	*get_zeroed_tab_and_advance_i(int *i, char c)
{
	char	*new;

	allocchk(new = walloc(3, SAFE));
	new[0] = c;
	new[1] = 0;
	(*i)++;
	return (new);
}

void	split_for_me(char **splitted, char *s, char *set)
{
	int	i;
	int	j;

	qmachine_reset();
	i = 0;
	j = 0;
	while (*s)
	{
		qmachine_update(*s);
		if (ft_strchr(set, *s) && !qmachine_getstate())
		{
			i = 0;
			j++;
			while (*s && ft_strchr(set, *s))
				s++;
		}
		if (*s && i == 0)
			splitted[j] = get_zeroed_tab_and_advance_i(&i, *s);
		else if (*s)
			splitted[j] = add_one_char(splitted[j], *s);
		if (*s)
			s++;
	}
	qmachine_reset();
	splitted[j + 1] = 0;
}

char	**split_not_in_quotes(char *s, char *set, int safety)
{
	char	**splitted;

	allocchk(splitted = walloc(pp_size(s, set) * sizeof(char *), safety));
	ft_bzero(splitted, pp_size(s, set));
	split_for_me(splitted, s, set);
	fflush(NULL);
	return (splitted);
}
