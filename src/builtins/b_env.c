/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:21:58 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/24 22:22:33 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	b_env(t_hash *envp, int fdo)
{
	int	ret;

	ret = 0;
	while (ret > -1 && envp)
	{
		if (ft_strcmp(envp->key, "?") && envp->value && ft_strcmp(envp->value,
				""))
		{
			if (ret > -1)
				ret = write(fdo, envp->key, ft_strlen(envp->key));
			if (ret > -1)
				ret = write(fdo, "=", 1);
			if (ret > -1)
				ret = write(fdo, envp->value, ft_strlen(envp->value));
			if (ret > -1)
				ret = write(fdo, "\n", 1);
			if (ret < 0)
			{
				ft_errno_error("b_env");
				return (-ret);
			}
		}
		envp = envp->next;
	}
	return (0);
}
