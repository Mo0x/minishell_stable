/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:04 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:38:27 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_parenthesis(t_list *lst)
{
	while (lst)
	{
		if (lst->data_type == INT_TYPE && (lst->content.int_val == OPENP || \
			lst->content.int_val == CLOSEP))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	replace_smc(char *s)
{
	if (*s == 3)
		*s = '|';
	else if (*s == 4)
		*s = '>';
	else if (*s == 5)
		*s = '<';
	else if (*s == 6)
		ft_memset(s, '>', 2);
	else if (*s == 14)
		ft_memset(s, '<', 2);
	else if (*s == 15)
		ft_memset(s, '&', 2);
	else if (*s == 16)
		ft_memset(s, '|', 2);
}

void	replace_silenced_metachars(t_asttree *t)
{
	t_list	*tmp;
	char	*s;
	int		i;

	tmp = NULL;
	if (t->l_param)
		tmp = t->l_param;
	while (tmp)
	{
		i = 0;
		while (tmp->data_type == STR_TYPE && tmp->content.str_val[i])
		{
			s = tmp->content.str_val + i;
			replace_smc(s);
			i++;
		}
		tmp = tmp->next;
	}
}

void	find_and_replace_lone_redirects(t_asttree *t)
{
	static char	voidness[] = {-6, -6, -6, 0};

	if (t->l_param && t->l_param->data_type == STR_TYPE && \
		!ft_memcmp(t->l_param->content.str_val, voidness, \
			ft_strlen(t->l_param->content.str_val)))
	{
		t->type = VOID;
		t->value = ft_strdup("void", SAFE);
		t->skip = 1;
	}
}

int	contains_nonblank_chars(char *prompt)
{
	while (*prompt)
	{
		if (!is_blank(*prompt))
			return (1);
		prompt++;
	}
	return (0);
}
