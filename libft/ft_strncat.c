/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:44:57 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:44:57 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char		*d;
	const char	*s;

	if (n != 0)
	{
		d = dst;
		s = src;
		while (*d != '\0')
			d++;
		while (*s != '\0' && n-- != 0)
			*d++ = *s++;
		*d = '\0';
	}
	return (dst);
}
