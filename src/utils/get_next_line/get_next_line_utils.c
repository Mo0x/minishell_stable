/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gecko <Gecko@chezmoi.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:19:20 by Gecko             #+#    #+#             */
/*   Updated: 2023/10/29 11:34:23 by Gecko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	gnl_ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_ft_strdup(const char *s)
{
	size_t	len;
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	len = gnl_ft_strlen(s);
	size = len + 1;
	str = walloc(len * sizeof(char) + 1, SAFE);
	if (!str)
		return (NULL);
	if (size > 0)
	{
		i = 0;
		while (s[i] && i < size - 1)
		{
			str[i] = s[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

char	*gnl_ft_substr(char *s, size_t start, size_t len)
{
	char	*tab;
	size_t	malloc_size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > gnl_ft_strlen(s))
		malloc_size = 1;
	else if (len > gnl_ft_strlen(s) - start)
		malloc_size = gnl_ft_strlen(s) - start + 1;
	else
		malloc_size = len + 1;
	tab = walloc(malloc_size * sizeof(char), SAFE);
	if (!tab)
		return (NULL);
	i = 0;
	while (malloc_size - 1 && s[i])
	{
		tab[i] = *(s + start);
		start++;
		malloc_size--;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

size_t	gnl_ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;
	size_t	copy_len;
	size_t	i;

	dst_len = gnl_ft_strlen(dst);
	src_len = gnl_ft_strlen(src);
	total_len = dst_len + src_len;
	if (size <= dst_len)
		return (src_len + size);
	copy_len = size - dst_len - 1;
	i = 0;
	while (i < copy_len && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	dst[dst_len + i] = '\0';
	return (total_len);
}

// Modified version of strjoin, to use with the destination
// already allocated on the heap. Handles wfreeing the old pointer

char	*ft_strjoin_s1_on_the_heap(char *s1, char *s2)
{
	char	*tab;
	size_t	total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1;
	tab = walloc((total_size) * sizeof(char), SAFE);
	if (!tab)
	{
		wfree(s1);
		return (NULL);
	}
	tab[0] = '\0';
	gnl_ft_strlcat(tab, s1, total_size);
	gnl_ft_strlcat(tab, s2, total_size);
	wfree(s1);
	return (tab);
}
