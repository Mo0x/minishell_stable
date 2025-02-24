/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:37 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:43 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsuffix(char *s, char *pattern)
{
	int	slen;
	int	pattern_len;

	if (!pattern)
		return (1);
	slen = ft_strlen(s);
	pattern_len = ft_strlen(pattern);
	while (slen > 0 && pattern_len > 0)
	{
		if (s[slen - 1] != pattern[pattern_len - 1])
			return (0);
		slen--;
		pattern_len--;
	}
	return (1);
}

int	ft_strprefix(char *s, char *pattern)
{
	if (!pattern)
		return (1);
	while (*s && *pattern)
	{
		if (*s != *pattern)
			return (0);
		s++;
		pattern++;
	}
	return (1);
}
