/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:41:42 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:41:45 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_size(int nb)
{
	int	size;

	if (nb > 0)
		size = 0;
	else
		size = 1;
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size + 1);
}

static void	recursive_itoa(char *tab, long int nb, int *i)
{
	if (nb < 0)
	{
		tab[*i] = '-';
		nb = -nb;
		(*i)++;
	}
	if (nb > 9)
	{
		recursive_itoa(tab, nb / 10, i);
	}
	tab[*i] = nb % 10 + '0';
	(*i)++;
}

char	*ft_itoa2(int n, int is_critical)
{
	long int	nb;
	char		*tab;
	int			i;
	int			size;

	i = 0;
	nb = n;
	size = get_size(n);
	allocchk(tab = walloc(size * sizeof(char), is_critical));
	if (!tab)
		return (NULL);
	recursive_itoa(tab, nb, &i);
	tab[i] = '\0';
	return (tab);
}

char	*ft_itoa(int n, int is_critical)
{
	long int	nb;
	char		*tab;
	int			i;
	int			size;

	i = 0;
	n &= 0x7FFFFF7F;
	nb = n;
	size = get_size(n);
	allocchk(tab = walloc(size * sizeof(char), is_critical));
	if (!tab)
		return (NULL);
	recursive_itoa(tab, nb, &i);
	tab[i] = '\0';
	return (tab);
}
