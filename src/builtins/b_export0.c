/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:22:55 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 22:30:48 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
TODO correct "export" with no arg
todo correct export when export =lol
*/

int	is_valid_variable_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

int	is_valid_var(char *s)
{
	while (*s)
	{
		if (!is_valid_variable_char(*s))
			return (FAILURE);
		s++;
	}
	return (SUCCESS);
}

static void	create_new_var(t_hash **hash, char *key, char *value)
{
	t_hash	*new;

	new = hashnew(key, value, CRITICAL);
	hash_addback(hash, new);
}

static void	update_var(t_hash *node, char *value)
{
	char	*s;

	wfree(node->value);
	s = ft_strdup(value, CRITICAL);
	node->value = s;
}

int	b_export(t_hash *envp, char *key, char *value)
{
	t_hash	*check_exists;

	if (!key)
		return (print_hashlist(envp), 0);
	check_exists = get_node_by_key(envp, key);
	if (!check_exists)
		create_new_var(&envp, key, value);
	else
		update_var(check_exists, value);
	return (SUCCESS);
}
/*
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

static int	ft_split_export(char *param, char **key, char **value, int *sum)
{
	char	*tmp;

	if (param[0] == '=')
	{
		error_print("qweqweshell: export: `%s': not a valid identifier\n",
			param);
		return (-1);
	}
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
*/

/*char	*backslasher(char *str)
{
	int		len;
	int		back;
	int		i;
	char	*ret;

	i = -1;
	back = 0;
	len = ft_strlen(str);
	while (str[++i])
		if (str[i] == '\"')
			back++;
	ret = walloc(sizeof(char) * (len + back + 1), 0);
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
}*/

/* int	ft_print_export(t_hash *envp, int fdo)
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
		if (ordered->value && ft_strcmp(ordered->value, ""))
		{
			if (ret > -1)
				ret = write(fdo, "=\"", 2);
			ordered->value = backslasher(ordered->value);
			if (ret > -1)
				ret = write(fdo, ordered->value, ft_strlen(ordered->value));
			if (ret > -1)
				ret = write(fdo, "\"\n", 2);
		}
		else
		{
			ret = write(fdo, "\n", 1);
		}
		if (ret < 0)
		{
			ft_errno_error("b_export");
			return (-ret);
		}
		ordered = ordered->next;
	}
	return (0);
} */

/* int	b_export_init(t_hash *envp, char **param, int fdo)
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
			{
				if (!ft_check_key_export(key))
				{
					if (sum && hash_getvalue(envp, key))
						value = ft_strjoin(hash_getvalue(envp, key), value, 0);
					b_export(envp, key, value);
				}
				else
				{
					error_print("qweqweshell: export: `%s': not a valid identifier\n",
						key);
					ret = 1;
				}
			}
			else
				return (1);
		}
	}
	else
		return (ft_print_export(envp, fdo));
	return (ret);
} */
