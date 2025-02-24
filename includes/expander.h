/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:05 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/24 22:11:33 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "typedefs.h"

//EXPANDER.H

void	expander(t_list **lst, t_hash *envp);

//QUOTES_REMOVER.C

void	quote_remover(t_list **lst);

//VARS

int		exp_vars(t_list **list, t_hash *vars);
void	free_lst(t_list **lst);

void	wildcards(t_list **lst);
int		get_file_list_len(t_list *lst);

// EXPANDER_UTILS.C
void	free_lst(t_list **lst);
void	putback_dollars(t_list *lst);
void	get_heredoc_next(t_list *lst);
void	setup_quotes_charset(char *s, char *set);

//WORD_SPLITTING.C
void	word_split(t_list **lst);

// VAR_EXPANDER_UTILS.C
int		is_valid_variable_char_with_exitstatus(char c);
char	*alloc_and_memset_ret(char *lst, char *toadd);
t_index	set_indexes_at_0(void);
char	*ft_stradd_one(char *lst, char *toadd, int pos);
int		is_special_char_that_doesnt_print_the_dollar(char c);

void	get_varkey_size_and_check_empty(char **s, int *size);
t_hash	*get_value(t_hash *vars, char *s);
void	empty_vars_checker(t_hash *varnode, int *to_free);
char	*replace_var(t_hash *varnode, char *s, char *og);
void	replace_quotes_with_negative_ascii(char *s);

void	replace_wildcard_with_1ascii_forfiles(char **s);
void	free_file_list(char ***fl);
void	replace_1ascii_with_wildcard(char ***tab);
void	replace_1_with_wild_single(char **str);
int		get_file_list_len(t_list *lst);
t_list	*look_for_wildcards_and_expand_if_found(t_list **lst, \
												t_list *tmp, \
												char **file_list);
char	**look_for_wildcards(char *s);
char	**get_wildcard_output(char *s);
char	**get_file_list_malloc(char *s);
void	advance_pattern_and_str(const char **pattern, char **str);
int		match_wildcard(const char *pattern, char *str);

int		cleanup_empty_var(t_list **head, t_list **lst);
#endif
