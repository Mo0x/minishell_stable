/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:44:10 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 15:54:35 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "typedefs.h"

t_nodetype	is_builtin(char *s);

// HASHTABLE.C

t_hash		*hashnew(char *key, char *value, int is_critical);
void		hash_addback(t_hash **hash, t_hash *node);
int			hash_size(t_hash *hash);
void		hash_clear(t_hash **hash);
char		*hash_getvalue(t_hash *hash, char *key);
int			hash_delone(t_hash **head, t_hash *to_del);
t_hash		*get_node_by_key(t_hash *hash, char *key);
int			hash_changevalue(t_hash **hash, char *key, char *new_value,
				int is_critical);
void		free_hashnode(t_hash *node);
void		print_hashlist(t_hash *hash);
t_hash		*ft_sort_hash_export(t_hash *envp);

// PATHS.C

// returns the path to the cmd if it exists.
// returns NULL if no path has been found.
char		*get_path(char *cmd, t_hash *envp);

// TOKEN_UTILS.C

int			get_single_token(char *s);
int			get_token_len(char *s);
int			get_token_pos(char *s);

// MLIST.C

t_list		*lstdup(t_list *lst);
int			is_token(t_list *n, int token);
void		ft_stack_init(t_stack *stack);
void		ft_stack_push(t_stack *stack, void *data, size_t size);
void		*ft_stack_pop(t_stack *stack);
void		*ft_stack_peek(t_stack *stack);
void		error_exit(char *error_str);
void		allocchk(void *ptr);
char		**split_not_in_quotes(char *s, char *set, int safety);
t_list		*ft_split_lst_charset(char *str, char *set, int is_critical);
void		error_print(char *f, ...);
int			is_blank(char c);
int			has_blank(char *s);

// QUOTE_MACHINE.C
int			quote_state_machine(char c, int type);
void		qmachine_update(char c);
int			qmachine_getstate(void);
void		qmachine_reset(void);

// MAIN_LOOP_CHECKS.C
int			has_parenthesis(t_list *lst);
void		replace_silenced_metachars(t_asttree *t);
void		find_and_replace_lone_redirects(t_asttree *t);
int			contains_nonblank_chars(char *prompt);

// HEREDOC_UTILS.C
void		heredoc_sigint_handler(int s);
void		heredoc_delimited_by_eof(int flag, int count, char *limiter);
void		init_heredoc(int *flag, int *count, char **ret);
int			limiter_is_read(int *flag, char **ret, char *limiter);
void		trim_newline(char *s);
int			read_limiter(char *ret, char *limiter, int *flag);
char		*get_heredoc_line(void);
char		*change_ret_to_130_and_return_null(t_hash *envp);
void		put_line_to_superpipe(int super_pipe, char *ret, int *count);
int			is_var_heredoc(char *s);

char		*ft_itoa(int n, int is_critical);
char		*ft_itoa2(int n, int is_critical);
#endif
