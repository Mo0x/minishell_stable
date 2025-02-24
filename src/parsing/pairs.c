/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:22 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:11:31 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pair_errors(t_pairs pairs)
{
	if (pairs.dquote % 2 != 0 || pairs.squote % 2 != 0)
	{
		error_print("%serror unclosed quote pair\n%s", BRED, CRESET);
		return (ERR_UNCLOSED_QUOTE);
	}
	else if (pairs.open_par != pairs.close_par)
	{
		error_print("%serror cannot find matching paranthesis\n%s", \
			BRED, CRESET);
		return (ERR_UNCLOSED_QUOTE);
	}
	return (SUCCESS);
}

//34 : "
//39 : '
//40 : ( 
//41 : )

int	check_pairs_inside_pairs(t_pairs *pairs, char *s)
{
	int	cur;
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == SQUOTE || s[i] == DQUOTE)
		{
			cur = s[i];
			i++;
			while (s[i] && s[i] != cur)
			{
				if (s[i] == DQUOTE && cur == SQUOTE)
					pairs->dquote--;
				if (s[i] == SQUOTE && cur == DQUOTE)
					pairs->squote--;
				i++;
			}
		}
		if (s[i])
			i++;
	}
	if (DEBUG)
		print_pairs(*pairs);
	return (SUCCESS);
}

int	check_pairs(char *s, t_msh *msh)
{
	int			i;
	t_pairs		pairs;

	i = 0;
	pairs.squote = 0;
	pairs.dquote = 0;
	pairs.close_par = 0;
	pairs.open_par = 0;
	while (s[i])
	{
		if (s[i] == 39)
			pairs.squote++;
		if (s[i] == 34)
			pairs.dquote++;
		else if (s[i] == 40)
			pairs.open_par++;
		else if (s[i] == 41)
			pairs.close_par++;
		i++;
	}
	check_pairs_inside_pairs(&pairs, s);
	msh->pairs.open_par = pairs.open_par;
	msh->pairs.close_par = pairs.close_par;
	return (pair_errors(pairs));
}

void	setup_quotes(char *s)
{
	int	i;
	int	cur;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			cur = s[i];
			i++;
			while (s[i] && s[i] != cur)
			{
				if (s[i] == 32)
					s[i] = 1;
				i++;
			}
		}
		if (s[i])
			i++;
	}
}

void	replace_1_with_space_lst(t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		if (tmp->data_type == STR_TYPE)
		{
			while (tmp->content.str_val[i])
			{
				if (tmp->content.str_val[i] == 1)
					tmp->content.str_val[i] = 32;
				i++;
			}
		}
		tmp = tmp->next;
	}
}
