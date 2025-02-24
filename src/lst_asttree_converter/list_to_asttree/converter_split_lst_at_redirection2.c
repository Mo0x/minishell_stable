/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_split_lst_at_redirection2.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:49:52 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:54 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redir_split_has_command(t_list **s)
{
	int	i;

	i = 0;
	while (s[i])
		if (has_command(s[i++]))
			return (i);
	return (0);
}
