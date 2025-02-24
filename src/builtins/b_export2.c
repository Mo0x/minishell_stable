/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:33:58 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/30 16:32:06 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_print_export1(t_hash *ordered, int fdo)
{
	int	ret;

	ret = 0;
	if (ret > -1)
		ret = write(fdo, "=\"", 2);
	ordered->value = backslasher(ordered->value);
	if (ret > -1)
		ret = write(fdo, ordered->value, ft_strlen(ordered->value));
	if (ret > -1)
		ret = write(fdo, "\"\n", 2);
	return (ret);
}

int	ft_print_export_error(void)
{
	ft_errno_error("qweqwe-shell: b_export");
	return (1);
}

int	ft_print_export(t_hash *envp, int fdo)
{
	int		ret;
	t_hash	*ordered;

	ret = 0;
	ordered = ft_sort_hash_export(envp);
	while (ret > -1 && ordered)
	{
		if (!ft_strcmp(ordered->key, "?"))
		{
			ordered = ordered->next;
			continue ;
		}
		if (ret > -1)
			ret = write(fdo, "declare -x ", 11);
		if (ret > -1)
			ret = write(fdo, ordered->key, ft_strlen(ordered->key));
		if (ordered->value)
			ret = ft_print_export1(ordered, fdo);
		else
			ret = write(fdo, "\n", 1);
		if (ret < 0)
			return (ft_print_export_error());
		ordered = ordered->next;
	}
	return (0);
}

int	b_export_init2(t_hash *envp, int *sum, char *value, char *key)
{
	if (!ft_check_key_export(key))
	{
		if (*sum && hash_getvalue(envp, key))
		{
			value = ft_strjoin(hash_getvalue(envp, key), value, 0);
		}
		b_export(envp, key, value);
		return (0);
	}
	else
	{
		error_print("qweqwe-shell: export: `%s': not a valid identifier\n", key);
		return (1);
	}
}

int	b_export_init(t_hash *envp, char **param, int fdo)
{
	char	*key;
	char	*value;
	int		sum;
	int		ret;
	int		i;

	i = 0;
	sum = 0;
	ret = 0;
	key = NULL;
	value = NULL;
	if (param[1])
	{
		while (param[++i])
		{
			if (!ft_split_export(param[i], &key, &value, &sum))
				ret = b_export_init2(envp, &sum, value, key);
			else
				return (1);
		}
	}
	else
		return (ft_print_export(envp, fdo));
	return (ret);
}
