/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:52:27 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/24 22:39:25 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dash_n(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		if (s[i] == '-')
		{
			i++;
			if (s[i] == 'n')
			{
				while (s[i] == 'n')
					i++;
				if (s[i] == '\0')
					return (1);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (0);
}

int	ft_dash_n(char **s, int *i)
{
	if (is_dash_n(s[*i]))
	{
		while (is_dash_n(s[*i]))
			*i += 1;
		return (1);
	}
	else
		return (0);
}

int	b_echo(char **s, int fd)
{
	int	flag;
	int	i;
	int	ret;

	i = 1;
	flag = ft_dash_n(s, &i);
	ret = 0;
	while (i < ft_count_param(s))
	{
		ret = write(fd, s[i], ft_strlen(s[i]));
		i++;
		if (ret < 0)
		{
			ft_errno_error("b_echo");
			return (-ret);
		}
		if (s[i])
			write(fd, " ", 1);
		ret = 0;
	}
	if (!flag)
		write(fd, "\n", 1);
	return (ret);
}
