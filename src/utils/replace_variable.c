/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:00:34 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 15:55:51 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *s, int n)
{
	int		len;
	char	*ret;
	int		i;

	len = 0;
	while (s[len] && len < n)
		len++;
	allocchk(ret = walloc(sizeof(char) * len + 1, SAFE));
	i = 0;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	ft_init_length(int *i, int *ret, char *str, int *len)
{
	*len = ft_strlen(str);
	*i = -1;
	*ret = 0;
}

static int	get_length(char *str, t_hash *envp)
{
	int		i;
	int		ret;
	int		len;
	int		var_len;
	char	*tmp;

	ft_init_length(&i, &ret, str, &len);
	while (++i < len)
	{
		if (str[i] == '$')
		{
			var_len = 0;
			while (ft_isalnum(str[i + 1 + var_len]) || str[i + 1 \
				+ var_len] == '_')
				var_len++;
			tmp = ft_strndup(str + i + 1, var_len);
			tmp = hash_getvalue(envp, tmp);
			if (tmp)
				ret += ft_strlen(tmp);
			i += var_len + 1;
		}
		else
			ret++;
	}
	return (ret);
}

char	*s_and_r(char *ret, char *str, t_hash *envp)
{	
	t_and_r	*t;

	t = init_s_and_r();
	while (++(t->i) < (int)ft_strlen(str))
	{
		if (str[t->i] == '$')
		{
			t->v = 0;
			while (aln(str[t->i + 1 + t->v]) || str[t->i + 1 + t->v] == '_')
				(t->v)++;
			t->tmp = ft_strndup(str + t->i + 1, t->v);
			t->tmp = hash_getvalue(envp, t->tmp);
			if (t->tmp)
			{
				ft_strcpy(ret + t->j, t->tmp);
				t->j += ft_strlen(t->tmp);
			}
			t->i += t->v;
		}
		else
			ret[(t->j)++] = str[t->i];
	}
	ret[t->j] = '\0';
	return (ret);
}
/*i = -1;
	j = 0;
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == '$')
		{
			var_len = 0;
			while (ft_isalnum(str[i + 1 + var_len]) || str[i + 1 \
				+ var_len] == '_')
				var_len++;
			tmp = ft_strndup(str + i + 1, var_len);
			tmp = hash_getvalue(envp, tmp);
			if (tmp)
			{
				ft_strcpy(ret + j, tmp);
				j += ft_strlen(tmp);
			}
			i += var_len;
		}
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}*/

char	*ft_replace_variable(char *str, t_hash *envp)
{
	char	*ret;
	int		ret_len;

	ret_len = 0;
	ret_len = get_length(str, envp);
	allocchk(ret = walloc(ret_len + 2, SAFE));
	ret = s_and_r(ret, str, envp);
	return (ret);
}
