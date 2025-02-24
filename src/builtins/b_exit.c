/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:39:56 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 16:36:53 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_an_al(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_overflow(int neg, unsigned long long num, int *error)
{
	if ((neg == 1 && num > LONG_MAX) || \
		(neg == -1 && num > -(unsigned int)LONG_MIN))
		*error = 1;
	return (*error);
}

static int	ft_atoi_overflow(const char *str, int *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) \
		|| str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (ft_overflow(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

unsigned int	b_exit_arg(t_asttree *node, int *skip)
{
	int	value;
	int	error;

	value = 0;
	error = 0;
	if (node->param[1])
		value = ft_atoi_overflow(node->param[1], &error);
	if (is_there_an_al(node->param[1]) || error)
	{
		write(2, "qweqwe-shell: exit:", 20);
		write(2, node->param[1], ft_strlen(node->param[1]));
		write(2, ": numeric argument required\n", 29);
		return (2);
	}
	else if (node->param[2])
	{
		write(2, "qweqwe-shell: exit: too many arguments\n", 40);
		*skip = 1;
		return (1);
	}
	return (value);
}

int	b_exit(t_asttree *node, t_hash *envp)
{
	unsigned long	value;
	int				skip;
	char			*tmp;

	skip = 0;
	if (!node || !node->param[1])
		tmp = hash_getvalue(envp, "?");
	value = ft_atoi(tmp);
	write(1, "exit\n", 5);
	if (node && node->param[1])
		value = b_exit_arg(node, &skip);
	if (skip)
		return (value);
	fds(0, 0);
	wclear(1);
	exit(value % 256);
	return (1);
}
/*
int	b_exit(t_asttree *node)
{
	int value;

	value = 0;
	if (node && node->param[1])
	{
		if (node->param[2])
		{
			write(1, "exit\n", 5);
			write(2, "qweqwe-shell: exit : too many arguments\n", 41);
			return (1);
		}
		if (node->param[1])
			value = ft_atoi(node->param[1]);
		if (is_there_an_al(node->param[1]))
		{
			write(1, "exit\n", 5);
			write(2, "qweqwe-shell: exit:", 20);
			write(2, node->param[1], ft_strlen(node->param[1]));
			write(2, ": numeric argument required\n", 29);
			exit(2);
		}
	}
	fds(0, 0);
	wclear(1);
	write(1, "exit\n", 5);
	exit(value % 255);
	return (1);
} */
