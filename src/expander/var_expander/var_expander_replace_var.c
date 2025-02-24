/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_replace_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:52:27 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 16:53:06 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_varkey_size_and_check_empty(char **s, int *size)
{
	(*s)++;
	*size = 0;
	while (**s && is_valid_variable_char_with_exitstatus(**s))
	{
		(*size)++;
		(*s)++;
	}
	if (*size == 0 && ft_strlen(*s) > 1 && *(s + 1) && \
			is_special_char_that_doesnt_print_the_dollar(*(*s + 1)))
	{
		*size = 0;
		(*size)++;
		ft_stradd_one(*s - 1, "l", 1);
	}
	*s -= *size;
}

// reads the key in the prompt and returns the corresponding value in
// envp. If the key is not found in envp, a dummy node is created for
// consistent logic across the functions.
t_hash	*get_value(t_hash *vars, char *s)
{
	int		size;
	char	*vartmp;
	t_hash	*varnode;
	int		i;

	i = 0;
	get_varkey_size_and_check_empty(&s, &size);
	allocchk(vartmp = walloc(size + 1, SAFE));
	while (size--)
	{
		vartmp[i] = *s;
		i++;
		s++;
	}
	vartmp[i] = 0;
	varnode = get_node_by_key(vars, vartmp);
	if (!varnode)
	{
		allocchk(varnode = walloc(sizeof(t_hash), SAFE));
		allocchk(varnode->key = ft_strdup(vartmp, SAFE));
		varnode->value = NULL;
	}
	wfree(vartmp);
	return (varnode);
}

void	empty_vars_checker(t_hash *varnode, int *to_free)
{
	if (!varnode->value)
	{
		if (ft_strlen(varnode->key) == 0)
		{
			wfree(varnode->value);
			allocchk(varnode->value = ft_strdup("$", SAFE));
		}
		else
			allocchk(varnode->value = ft_strdup("", SAFE));
		*to_free = 1;
	}
}

// reads the variable name from the prompt starting at the $ sign,
// and places its corresponding value inside vartmp.
// if no key is found for the specified variable, a dummy varnode is created
// with an empty string as value and the found var as key. 
// it is NOT added to the varlist.
char	*replace_var(t_hash *varnode, char *s, char *og)
{
	char	*expanded;
	int		varstart;
	int		varend;
	int		to_free;
	ssize_t	varvalue_len;

	to_free = 0;
	empty_vars_checker(varnode, &to_free);
	replace_quotes_with_negative_ascii(varnode->value);
	varvalue_len = ft_strlen(varnode->value);
	varstart = ft_abs(og - ft_strstr(og, s));
	varend = ft_abs(varstart + ft_strlen(varnode->key));
	allocchk(expanded = walloc(ft_strlen(og) + varvalue_len - \
				ft_strlen(varnode->key) + ft_strlen(og), SAFE));
	ft_strcpy(expanded, og);
	ft_memmove(expanded + varstart + varvalue_len, \
				expanded + varend + 1, ft_strlen(expanded + varend));
	ft_memcpy(expanded + varstart, varnode->value, varvalue_len);
	expanded[ft_strlen(og) + varvalue_len - \
				ft_strlen(varnode->key) - 1] = 0;
	if (to_free == 1)
		free_hashnode(varnode);
	wfree(og);
	return (expanded);
}
