/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:49:09 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:44 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int is_critical)
{
	char	*tab;
	size_t	total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = walloc((total_size) * sizeof(char), is_critical);
	if (!tab)
		return (NULL);
	tab[0] = '\0';
	ft_strlcat(tab, s1, total_size);
	ft_strlcat(tab, s2, total_size);
	return (tab);
}
