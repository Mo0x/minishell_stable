/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:44:42 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:49:25 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_param_list(t_list *param)
{
	int	ret;

	ret = 0;
	if (param)
	{
		while (param)
		{
			ret++;
			param = param->next;
		}
	}
	return (ret);
}

int	ft_count_param(char **param)
{
	int	ret;

	ret = 0;
	if (param)
	{
		while (param[ret])
			ret++;
	}
	return (ret);
}
