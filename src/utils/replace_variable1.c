/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:40:52 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 17:47:37 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*had to do this for norm*/

int	aln(int c)
{
	if (!ft_isalpha(c) && !ft_isdigit(c))
		return (0);
	return (8);
}

t_and_r	*init_s_and_r(void)
{
	t_and_r	*ret;

	ret = walloc(sizeof(t_and_r) * 1, SAFE);
	if (!ret)
		ft_eq("error malloc init_s_and_r");
	ret->i = -1;
	ret->j = 0;
	ret->v = 0;
	ret->tmp = NULL;
	return (ret);
}
