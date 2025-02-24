/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:04:24 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 18:14:11 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "../libft/libft.h"

typedef struct s_par_depthsplit
{
	t_list				*lst;
	int					depth;
	int					parindex;
}						t_par_depthsplit;

typedef struct s_index
{
	int					i;
	int					j;
	int					k;
}						t_index;

typedef struct s_stack_node
{
	void				*data;
	struct s_stack_node	*next;
}						t_stack_node;

typedef struct s_stack
{
	t_stack_node		*top;
}						t_stack;
typedef struct s_hash
{
	char				*key;
	char				*value;
	struct s_hash		*next;
}						t_hash;

typedef struct s_var_expander
{
	t_hash				*varnode;
	char				*expanded;
	int					key_len;
}						t_var_expander;

typedef struct s_pairs
{
	int					dquote;
	int					squote;
	int					open_par;
	int					close_par;
}						t_pairs;

typedef struct s_cmdlst
{
	t_list				*cmdlst;
	char				**tinfos;
	int					cmdnb;
}						t_cmdlst;

typedef struct s_vars
{
	char				*token;
	char				*value;
}						t_vars;

typedef struct s_sort_hash
{
	t_hash				*ret;
	t_hash				*sorted;
	t_hash				*current;
	t_hash				*next;
}						t_sort_hash;

typedef enum e_type
{
	BUILTIN,
	COMMAND,
	AND_OP,
	OR_OP,
	PIPE_OP,
	REDIRECTION,
	SUBTREE,
	TMP_SUBTREE,
	VOID,
	ERROR
}						t_nodetype;

typedef struct s_asttree
{
	t_nodetype			type;
	char				*value;
	char				**param;
	t_list				*l_param;
	struct s_asttree	**children;
	struct s_asttree	*parent;
	int					num_child;
	int					to_close;
	pid_t				pid;
	int					fdi;
	int					fdo;
	int					skip;
	char				*here_doc;
	char				*stached_heredoc;
	int					lst;
	int					index;
	int					depth;
	int					pargroup;
	int					is_last_logical_node;
}						t_asttree;

typedef struct s_pipe
{
	struct s_pipe		*next;
	int					entree;
	int					exit;
}						t_pipe;

typedef struct s_logicaltree
{
	t_asttree			**logicaltree;
	int					size;
}						t_logicaltree;

typedef struct s_msh
{
	t_cmdlst			cmdlst;
	t_hash				*vars;
	t_pairs				pairs;
}						t_msh;

typedef struct s_potential_parents
{
	int					index;
	int					is_tmp_subtree;
	t_asttree			*ptr;
}						t_potential_parents;

typedef struct s_fds
{
	int					fd;
	struct s_fds		*next;
}						t_fds;

typedef struct s_and_r
{
	int					i;
	int					j;
	int					v;
	char				*tmp;
}						t_and_r;

#endif
