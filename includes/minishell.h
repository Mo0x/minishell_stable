/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:48:50 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 15:57:29 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include "converter.h"
# include "debug.h"
# include "defines.h"
# include "environment.h"
# include "expander.h"
# include "get_next_line.h"
# include "parsing.h"
# include "tokenizer.h"
# include "utils.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile int	g_signal_status;

/*ASCII*/

void				ft_ascii(void);

/*Error*/

int					ft_error(char *msg);
void				ft_eq(char *msg);
int					ft_errno_error(char *msg);
int					ft_error(char *msg);
char				*ft_cmd_notfound_error(char *cmd, int stdin, int stdout);

/*ast tree utilities*/

t_asttree			*asttree_create_node(t_nodetype type, char *data,
						char **param);
void				asttree_addchild(t_asttree *parent, t_asttree *child);
void				asttree_delete_node(t_asttree *node);
void				asttree_preorder(t_asttree *node, void (*f)(t_asttree *));
void				asttree_postorder(t_asttree *node, void (*f)(t_asttree *));
void				ft_freetab(void **to_free);
void				asttree_clear(t_asttree *root);
void				asttree_expand_tree(t_asttree *node);
int					ft_count_param_list(t_list *param);
int					ft_count_param(char **s);
void				ft_param_expander(t_asttree *node, t_hash *envp);
void				asttree_clear(t_asttree *root);
void				check_tree_for_missing_childs(t_asttree *node, int *ptr);
void				asttree_addchild_before(t_asttree *parent,
						t_asttree *child);
char				*ft_replace_variable(char *str, t_hash *envp);

/*exec*/

int					ft_fork_exec(t_asttree *node, t_hash *envp, int *lst_sts);
int					ft_executor(t_asttree *node, t_hash *envp, int fork);
int					ft_exec(t_asttree *node, t_hash *envp);
int					ft_exec_builtin(t_asttree *node, t_hash *envp);
int					ft_exec_command(t_asttree *node, t_hash *envp, int fork);
int					ft_exec_fork(t_asttree *node, t_hash *envp, int stdin,
						int stdout);
int					ft_cmd_executor(t_asttree *node, t_hash *envp, int stdin,
						int stdout);
int					ft_exec_subtree(t_asttree *node, t_hash *envp);
void				execution(t_asttree *node, t_hash *envp);
void				ft_exec_command_fds(int stdout, int stdin);

/* Pipe and redir */

int					ft_exec_pipe(t_asttree *node, t_hash *envp);
int					ft_redir_init(t_asttree *node, t_hash *envp);
int					ft_exec_expand_redir(t_asttree *node, t_hash *envp);
int					ft_heredoc_init(t_asttree *node, t_hash *envp);
char				*ft_heredoc_pipe(char *limiter, t_hash *envp);
t_asttree			*ft_nxt_cmd(t_asttree *node);
int					ft_or(t_asttree *node, t_hash *envp);
int					ft_and(t_asttree *node, t_hash *envp);
int					ft_redir_solo(t_asttree *node, t_hash *envp);
int					ft_void(t_asttree *node, t_hash *envp);
int					ft_heredoc_solo(char *limiter, t_hash *envp);
t_fds				*create_fd(int fd);
void				add_back_fds(t_fds *dad, t_fds *child);
void				close_fds(t_fds *head);
void				fds(int fd, int new);
void				pipe_handler(int pipe_to_do[2], int new);
int					ft_exec_heredoc(t_asttree *node, t_hash *envp);
t_asttree			*ft_lstpipedcmd(t_asttree *node);
int					ft_exec_pipeline(t_asttree *node, t_hash *envp);
int					ft_lstcmd(t_asttree *node, t_hash *envp, int forks);
void				close_pipe(t_pipe *head);
void				pipe_handler(int pipe_to_do[2], int new);
int					ft_void(t_asttree *node, t_hash *envp);
t_and_r				*init_s_and_r(void);
int					aln(int c);

/* signal*/

char				*convert_type(t_nodetype type);
void				get_potential_parents(t_asttree *node,
						t_potential_parents *pp, int *index, int target_depth);
int					is_logical_node(t_asttree *node);
void				set_signals(int signum, int type, int flags,
						void (*handler)(int));
void				sigint_handler(int signum);
void				set_interactive_signals(void);
void				set_signals_to_default(void);

# ifndef DEBUG
#  define DEBUG 0
# endif

#endif
