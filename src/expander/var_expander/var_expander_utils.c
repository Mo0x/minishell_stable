/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:19 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 16:53:21 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_variable_char_with_exitstatus(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z') || \
			(c == '_') || (c == '?')) || \
			(c >= '0' && c <= '9'));
}

char	*alloc_and_memset_ret(char *lst, char *toadd)
{
	char	*ret;

	allocchk(ret = walloc(ft_strlen(lst) + ft_strlen(toadd) + 1, SAFE));
	ft_memset(ret, 0, ft_strlen(lst) + ft_strlen(toadd) + 1);
	return (ret);
}

t_index	set_indexes_at_0(void)
{
	t_index	lovelanorme;

	lovelanorme.i = 0;
	lovelanorme.j = 0;
	lovelanorme.k = 0;
	return (lovelanorme);
}

char	*ft_stradd_one(char *lst, char *toadd, int pos)
{
	char	*ret;
	t_index	i;

	ret = alloc_and_memset_ret(lst, toadd);
	i = set_indexes_at_0();
	while (i.i < pos)
	{
		ret[i.i] = *lst;
		i.i++;
		lst++;
	}
	while (toadd[i.j])
	{
		ret[i.i] = toadd[i.j];
		i.j++;
		i.i++;
	}
	while (*lst)
	{
		ret[i.i] = *lst;
		lst++;
		i.i++;
	}
	ret[i.i] = 0;
	return (ret);
}

int	is_special_char_that_doesnt_print_the_dollar(char c)
{
	return (c == 34 || c == 39 || c == '(' || c == ')');
}
