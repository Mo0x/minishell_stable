/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:58 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:12:04 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// allocates a new char* on the heap and performs a custom strdup on it
// taking the original str from the token. the original string is freed
// in the parent function.
// replacement is perfomed on wildcards and dollars in quotes.

static char	replace_wildcard_and_dollar(char c, int qstate)
{
	if (c == '*')
		return (1);
	else if (c == '$' && qstate == 39)
		return (2);
	else
		return (c);
}

static void	parse_inside_quotes(char *s, char *qremoved, t_index *index, \
								int *quote_type)
{
	if (s[index->i] == 34 || s[index->i] == 39)
	{
		*quote_type = s[index->i];
		index->i++;
		while (s[index->i] && s[index->i] != *quote_type)
		{
			s[index->i] = replace_wildcard_and_dollar(s[index->i], *quote_type);
			qremoved[index->j] = s[index->i];
			index->i++;
			index->j++;
		}
		if (s[index->i] && s[index->i] == *quote_type)
			index->i++;
	}
}

static char	*remove_quotes(char *s)
{
	int		quote_type;
	t_index	index;
	char	*qremoved;

	quote_type = -1;
	index.i = 0;
	index.j = 0;
	allocchk(qremoved = walloc(ft_strlen(s) + 1, SAFE));
	while (s[index.i])
	{
		parse_inside_quotes(s, qremoved, &index, &quote_type);
		if (s[index.i] && s[index.i] != 34 && s[index.i] != 39)
		{
			qremoved[index.j] = s[index.i];
			index.j++;
			index.i++;
		}
	}
	qremoved[index.j] = 0;
	return (qremoved);
}

// this function will replace the str value of nodes inside the list with 
// a new byte array, without the quotes.

void	quote_remover(t_list **lst)
{
	t_list	*tmp;
	char	*stemp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->data_type == STR_TYPE)
		{
			stemp = remove_quotes(tmp->content.str_val);
			wfree(tmp->content.str_val);
			tmp->content.str_val = stemp;
		}
		tmp = tmp->next;
	}
}
