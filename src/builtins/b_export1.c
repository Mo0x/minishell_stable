/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:28:10 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/30 21:22:47 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_key_export(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]))
		return (-1);
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (-1);
	return (0);
}

int	ft_split_export_error(char *param)
{
	error_print("qweqweshell: export: `%s': not a valid identifier\n",
		param);
	return (-1);
}

int	ft_split_export(char *param, char **key, char **value, int *sum)
{
	char	*tmp;

	if (param[0] == '=')
		return (ft_split_export_error(param));
	*key = ft_strdup(param, 0);
	tmp = ft_strchr(*key, '=');
	if (!tmp)
		key = NULL;
	else
	{
		if (*(tmp - 1) == '+')
		{
			*sum = 1;
			*(tmp - 1) = 0;
		}
		else
			tmp[0] = 0;
	}
	*value = ft_strchr(param, '=');
	if (*value && (*value)[1])
		*value = *value + 1;
	else
		*value = "";
	return (0);
}

int	backslasher_count(char *str)
{
	int	ret;
	int	back;
	int	i;

	i = -1;
	ret = ft_strlen(str);
	back = 0;
	while (str[++i])
		if (str[i] == '\"')
			back++;
	return (back + ret + 1);
}

char	*backslasher(char *str)
{
	int		len;
	int		i;
	char	*ret;

	ret = walloc(sizeof(char) * backslasher_count(str), 0);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			ret[len] = '\\';
			len++;
		}
		ret[len] = str[i];
		len++;
	}
	ret[len] = 0;
	wfree(str);
	return (ret);
}
