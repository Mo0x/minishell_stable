/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:58 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:12:04 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	replace_quotes_with_negative_ascii(char *s)
{
	while (*s)
	{
		if (*s == 34)
			*s = -5;
		else if (*s == 39)
			*s = -6;
		s++;
	}
}

void	parse_inside_quotes_and_replace_vars(t_var_expander *exp, \
											int cq, char **s, \
											t_hash *vars)
{
	cq = **s;
	(*s)++;
	while (**s && **s != cq)
	{
		if (**s == '$' && cq != 39)
		{
			exp->varnode = get_value(vars, *s);
			exp->key_len = ft_strlen(exp->varnode->key);
			exp->expanded = replace_var(exp->varnode, *s, exp->expanded);
			*s += exp->key_len;
		}
		(*s)++;
	}
}

void	replace_var_on_dollar_sign(t_var_expander *exp, char **s, t_hash *vars)
{
	if (**s == '$')
	{
		exp->varnode = get_value(vars, *s);
		exp->key_len = ft_strlen(exp->varnode->key);
		exp->expanded = replace_var(exp->varnode, *s, exp->expanded);
		*s += exp->key_len;
	}
}

// Parses the whole prompt and sends the current s pointer value
// to the fetcher when it finds a $ sign. important to note that
// quote gestion is done here for variables.
static char	*look_for_vars(t_hash *vars, char *s)
{
	char			*og;
	int				cur_quote;
	t_var_expander	exp;

	if (!ft_strchr(s, '$'))
		return (s);
	og = s;
	cur_quote = 0;
	allocchk(exp.expanded = ft_strdup(s, SAFE));
	while (*s)
	{
		if (*s == 39 || *s == 34)
			parse_inside_quotes_and_replace_vars(&exp, cur_quote, &s, vars);
		else
			replace_var_on_dollar_sign(&exp, &s, vars);
		cur_quote = 0;
		if (*s)
			s++;
	}
	wfree(og);
	return (exp.expanded);
}

// iterates over the tokens and expand variables inside them.
// if an expension results in an empty string, then the token is deleted
// and removed from the list.
int	exp_vars(t_list **head, t_hash *vars)
{
	t_list	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->data_type == STR_TYPE)
		{
			lst->content.str_val = look_for_vars(vars, \
										lst->content.str_val);
			if (ft_strlen(lst->content.str_val) == 0)
				if (cleanup_empty_var(head, &lst))
					continue ;
		}
		if (lst)
			lst = lst->next;
	}
	return (SUCCESS);
}
