/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:43:32 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/24 21:43:33 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# include "typedefs.h"

void	print_prompt_split(char *prompt);
void	print_token_lst(t_list *lst);
void	print_commands(t_cmdlst *cmdlst);
void	print_pairs(t_pairs pairs);
void	mock_vars(t_msh *msh);
void	print_vars(t_msh msh);
void	graph(t_asttree *ast);
void	print_logicaltree(t_asttree **tree);
void	print_par_infos(t_par_depthsplit **pardsplit);
#endif
