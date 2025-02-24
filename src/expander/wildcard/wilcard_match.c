/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:20:28 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/24 22:12:08 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	advance_pattern_and_str(const char **pattern, char **str)
{
	(*pattern)++;
	(*str)++;
}

int	match_wildcard(const char *pattern, char *str)
{
	if (*pattern == '*' && !pattern[1])
		return (true);
	replace_wildcard_with_1ascii_forfiles(&str);
	while (*pattern && *str)
	{
		if (*pattern == *str || *pattern == '?')
			advance_pattern_and_str(&pattern, &str);
		else if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (true);
			while (*str)
			{
				if (match_wildcard(pattern, str))
					return (true);
				str++;
			}
			return (false);
		}
		else
			return (false);
	}
	return (!*pattern && !*str);
}
