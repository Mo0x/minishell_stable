/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:51 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/14 14:46:53 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quotes(char *s)
{
	int	quote_type;

	quote_type = -1;
	if (s[0] == 34 || s[0] == 39)
		quote_type = s[0];
	if (s[ft_strlen(s) - 1] == quote_type)
		return (SUCCESS);
	return (FAILURE);
}

void	defragment_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->data_type == STR_TYPE && ft_strlen(tmp->content.str_val) == 0)
		{
			next = tmp->next;
			ft_lstdelone(lst, tmp);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
}

int	replace_metachars_with_silencing_chars(char *s)
{
	if (!ft_strncmp(s, "|", 1))
		return (*s = 3, 0);
	else if (!ft_strncmp(s, ">", 1))
		return (*s = 4, 0);
	else if (!ft_strncmp(s, "<", 1))
		return (*s = 5, 0);
	else if (*(s + 1) && !ft_strncmp(s, ">>", 2))
		return (*s = 6, *(s + 1) = 6, 1);
	else if (*(s + 1) && !ft_strncmp(s, "<<", 2))
		return (*s = 14,*(s + 1) = 14, 1);
	else if (*(s + 1) && !ft_strncmp(s, "&&", 2))
		return (*s = 15, *(s + 1) = 15, 1);
	else if (*(s + 1) && !ft_strncmp(s, "||", 2))
		return (*s = 16,*(s + 1) = 16, 1);
	return (0);
}

void	add_void_nodes_before_lone_redirects(t_list **lst)
{
	t_list		*tmp;
	static char	voidness[4] = {-6, -6, -6, 0};

	tmp = *lst;
	if (is_redirection(tmp))
		ft_lstadd_before(lst, tmp, ft_lstnew(voidness, STR_TYPE, SAFE));
	while (tmp)
	{
		if (!is_separating_token(tmp) && tmp->next && is_redirection(tmp->next))
			ft_lstadd_after(lst, ft_lstnew(voidness, STR_TYPE, SAFE), tmp);
		tmp = tmp->next;
	}
}

char	*silence_metachars_in_quotes(char *prompt)
{
	char	*silenced_mc;
	int		i;
	int		cur_quote;

	allocchk(silenced_mc = ft_strdup(prompt, SAFE));
	wfree(prompt);
	i = 0;
	cur_quote = 0;
	while (silenced_mc[i])
	{
		if (!cur_quote && (silenced_mc[i] == 34 || silenced_mc[i] == 39))
			cur_quote = silenced_mc[i];
		else if (cur_quote && (silenced_mc[i] == cur_quote))
			cur_quote = 0;
		else if (cur_quote)
			i += replace_metachars_with_silencing_chars(silenced_mc + i);
		i++;
	}
	return (silenced_mc);
}
