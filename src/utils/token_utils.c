/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:12:21 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:12:22 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_token(t_list *n, int token)
{
	return (n && n->data_type == INT_TYPE && n->content.int_val == token);
}

int	get_single_token(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (PIPE);
	else if (!ft_strcmp(s, "<"))
		return (LESS);
	else if (!ft_strcmp(s, "<<"))
		return (DLESS);
	else if (!ft_strcmp(s, ">"))
		return (GREAT);
	else if (!ft_strcmp(s, ">>"))
		return (DGREAT);
	else if (!ft_strcmp(s, "&&"))
		return (AND);
	else if (!ft_strcmp(s, "||"))
		return (OR);
	else if (!ft_strcmp(s, "("))
		return (OPENP);
	else if (!ft_strcmp(s, ")"))
		return (CLOSEP);
	else
		return (FAILURE);
}

int	get_token_len(char	*s)
{
	if (!ft_strncmp(s, "||", 2))
		return (2);
	if (!ft_strncmp(s, "&&", 2))
		return (2);
	if (!ft_strncmp(s, "<<", 2))
		return (2);
	if (!ft_strncmp(s, ">>", 2))
		return (2);
	if (!ft_strncmp(s, "|", 1))
		return (1);
	if (!ft_strncmp(s, "<", 1))
		return (1);
	if (!ft_strncmp(s, ">", 1))
		return (1);
	if (!ft_strncmp(s, "(", 1))
		return (1);
	if (!ft_strncmp(s, ")", 1))
		return (1);
	return (-1);
}

int	get_token_pos(char	*s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, "||", 2) || !ft_strncmp(s + i, "&&", 2) || \
			!ft_strncmp(s + i, "<<", 2) || !ft_strncmp(s + i, ">>", 2))
			return (i);
		if (!ft_strncmp(s + i, "|", 1))
			return (i);
		if (!ft_strncmp(s + i, "<", 1))
			return (i);
		if (!ft_strncmp(s + i, ">", 1))
			return (i);
		if (!ft_strncmp(s + i, "(", 1))
			return (i);
		if (!ft_strncmp(s + i, ")", 1))
			return (i);
		i++;
	}
	return (-1);
}
