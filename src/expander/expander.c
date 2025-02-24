/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:58 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:12:03 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_negaive_ascii_with_correct_quotes(t_list *lst)
{
	char	*s;

	while (lst)
	{
		if (lst->data_type == STR_TYPE)
		{
			s = lst->content.str_val;
			while (*s)
			{
				if (*s == -5)
					*s = 34;
				else if (*s == -6)
					*s = 39;
				s++;
			}
		}
		lst = lst->next;
	}
}

// bash expands in this order (in the minishell scope) :
// -vars
// retokenization of the IFS characters in vars. IFS is no longer supported
// as of v-3daybeforepush because of pesky bugs and i want to be done with
// this *** project
// -quotes
// -wildcards
// a 2 ascii has been used to store $ in single quotes,
// hence the putback dollars function
// if the expansion of variable concludes in an empty token list,
// then it returns immediately.
void	expander(t_list **lst, t_hash *envp)
{
	exp_vars(lst, envp);
	if (!*lst)
		return ;
	word_split(lst);
	quote_remover(lst);
	wildcards(lst);
	replace_negaive_ascii_with_correct_quotes(*lst);
	get_heredoc_next(*lst);
	putback_dollars(*lst);
}
