/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:10 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 17:32:10 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedefs.h"

//PARSING.C
int			parser(char *prompt, t_msh *msh);
t_list		*tokenize(char *prompt, t_msh *msh);
int			get_single_token(char *s);

//PAIRS.C
int			pair_errors(t_pairs pairs);
int			check_pairs(char *s, t_msh *msh);
int			check_pairs_inside_pairs(t_pairs *pairs, char *s);
void		setup_quotes(char *s);
void		replace_1_with_space_lst(t_list *lst);

//PARSING_ERROR.C
int			token_missplacement(t_list *lst);
int			nested_parenthesis(t_list *lst);
void		search_and_destroy_useless_parenthesis(t_msh *msh, t_list **lst);

//TOKENIZATION.C
int			is_in_quotes(char *s);

//LIST TO TREE CONVERSION
t_asttree	*convert_list_to_asttree(t_msh *msh, t_list **lst, \
								int has_parenthesis);

char		**env_conv(t_hash *vars);

int			is_redirection(t_list *node);

t_asttree	*setup_parenthesis_stuff(t_list **lst);
int			is_separating_token(t_list *node);
char		*convert_define_to_str(int define);
int			usefull_tokens(t_list *node);
int			has_logical_token_before_opening_parenthesis(t_list *node, \
													t_list **lst);
void		defragment_lst(t_list **lst);
int			replace_metachars_with_silencing_chars(char *s);
void		add_void_nodes_before_lone_redirects(t_list **lst);
char		*silence_metachars_in_quotes(char *prompt);
void		split_tokens_inside_strtypes(t_list **lst);
#endif
