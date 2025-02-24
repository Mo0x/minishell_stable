/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtablen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:54:27 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/15 12:54:44 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tabtablen(char **tab)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tab[i])
	{
		size += ft_strlen(tab[i]);
		i++;
	}
	return (size);
}
