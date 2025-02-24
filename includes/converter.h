/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:25 by achatzit          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:11 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

# include "typedefs.h"

// SETUP_PARENTHESIS_UTILS.C
int					is_parenthesis(t_list *lst);
int					is_end_of_prompt_at_depth_zero(t_list *lst);
int					has_tmp_subtree(t_asttree *node);
void				index_nodes(t_list *lst);
void				depth_calculator(t_list *lst);

// SETUP_PARENTHESIS_UTILS2.C
int					get_parsplit_count(t_list *lst);
t_list				*lstdup(t_list *lst);
t_list				*whole_lstdup(t_list *lst);
void				skip_parenthesis_and_put_starnewlst_at_1_if_so(t_list **lst,
						int *snlst);
t_list				*dup_lst_and_put_newlst_at_0(t_list *lst, int *snlst);

// SETUP_PARENTHESIS_UTILS3.C
int					get_orphaned_trees_nb(t_asttree **s);
void				setup_join_orphan(t_index *i, t_potential_parents *clst,
						int *dist);
int					get_pp_array_size(t_asttree **s, int dtf);
t_asttree			*join_subtrees(t_asttree **s);
int					get_highest_par_group_index(t_par_depthsplit **p);

// SETUP_PARENTHESIS_UTILS4.C
t_list				*join_parenthesis_group(int group, t_par_depthsplit **p);
t_asttree			*join_subtrees(t_asttree **s);

// POTENTIAL_PARENTS.C
t_asttree			**create_potential_parents(t_asttree **s, int dtf);
t_potential_parents	*fill_potential_parents(t_asttree **potential_parents,
						int dtf);
void				join_orphan_subtree_with_parent(t_asttree *c, t_asttree **s,
						int depth_to_find);

// CONVERTER
t_nodetype			convert_token_num(int token);
t_nodetype			is_builtin(char *s);
char				*get_redirect_data(int token);
int					is_int_but_not_redirect(t_list *lst);
int					lst_redirects_count(t_list *lst);
int					get_number_of_inttypes_nonredirect_tokens(t_list *lst);
void				add_node_dupeuntil(t_list **prev, t_list **new,
						t_list **head);
int					is_cmd_a_child(t_asttree *lnode, t_asttree *cnode);
int					get_index_of_last_node_in_the_command(t_asttree *n);
int					find_parent_at_the_right_of_child(t_asttree *c,
						t_asttree **p, int i);
int					find_parent_at_the_left_of_child(t_asttree *c,
						t_asttree **p, int i);
void				join_child_with_parent(t_asttree *c, t_asttree **p);
void				check_if_logical_nodes_need_tmpsubtrees(t_asttree *n);
void				index_last_logical_node(t_asttree *n);
t_logicaltree		*get_logical_nodes_tab(t_list *lst, int size, int i);
t_list				*lst_dupe_node(t_list *node);
t_list				*lst_dupe_n(t_list *lst, int n);
t_list				*lst_dupe_until_redirection(t_list *lst);
t_asttree			*get_node_from_lst(t_list *lst);
t_list				*convert_lst_to_readable_lparam_for_exec(t_list *lst);
t_asttree			*return_pure_node(t_list *lst);
t_asttree			*get_command_as_asttree(t_list *lst);
t_asttree			*single_command_logic(t_list *lst);
t_asttree			*create_cmd_node(t_list **lst);
t_logicaltree		*single_command(t_list *lst, t_logicaltree *tree);
t_logicaltree		*get_commands_nodes_tab(t_list *lst, int size, int i);
t_asttree			*create_subtree(t_logicaltree *ltree);
t_asttree			*join_trees_with_parenthesis(t_logicaltree *ltree,
						t_logicaltree *ctree);
t_asttree			*join_trees_no_parenthesis(t_logicaltree *ltree,
						t_logicaltree *ctree);
t_list				**split_lst_at_redirection(t_list **lst, int redirect_nb);
t_list				**put_command_at_the_start_in_case_of_redir_file_command(\
					t_list **lst);
int					has_command(t_list *lst);
int					is_void(t_list *node);
int					redir_split_has_command(t_list **s);

void				flag_lstnodes(t_list *lst);

// COMMAND MAKER
t_list				*cat_command(t_list *lst);
t_list				*get_command_node(t_list *lst);
int					join_command(t_list **lst);
void				cmd_join(t_list **lst);

#endif
