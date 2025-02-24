/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:22 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:11:32 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// main function for the parsing part

int	parser(char *prompt, t_msh *msh)
{
	if (DEBUG)
		print_prompt_split(prompt);
	msh->cmdlst.cmdlst = tokenize(prompt, msh);
	if (msh->cmdlst.cmdlst == NULL)
		return (FAILURE);
	if (token_missplacement(msh->cmdlst.cmdlst) == FAILURE)
		return (FAILURE);
	search_and_destroy_useless_parenthesis(msh, &msh->cmdlst.cmdlst);
	if (DEBUG)
		print_token_lst(msh->cmdlst.cmdlst);
	return (SUCCESS);
}
