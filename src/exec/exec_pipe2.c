/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:09:14 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/31 21:12:12 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipe	*create_pipe(int entree, int exit)
{
	t_pipe	*new;

	new = walloc(sizeof(t_pipe), SAFE);
	if (!new)
		ft_eq("ERROR MALLOC create pipe");
	new->entree = entree;
	new->exit = exit;
	new->next = NULL;
	return (new);
}

void	add_pipe(t_pipe *dad, t_pipe *child)
{
	if (!dad)
		return ;
	else
	{
		while (dad->next)
			dad = dad->next;
		dad->next = child;
	}
}

void	pipe_handler(int pipe_to_do[2], int new)
{
	static t_pipe	*head = NULL;
	t_pipe			*my_pipe;

	if (new == 1)
	{
		if (!head)
			head = create_pipe(pipe_to_do[0], pipe_to_do[1]);
		else
		{
			my_pipe = create_pipe(pipe_to_do[0], pipe_to_do[1]);
			add_pipe(head, my_pipe);
		}
	}
	else
	{
		close_pipe(head);
		head = NULL;
	}
}

char	*ft_heredoc_pipe(char *limiter, t_hash *envp)
{
	char	*ret;
	char	*join;
	int		flag;
	int		count;

	join = "";
	init_heredoc(&flag, &count, &ret);
	g_signal_status = 0;
	while (1)
	{
		ret = get_heredoc_line();
		if (g_signal_status == SIGINT)
			return (change_ret_to_130_and_return_null(envp));
		if (!ret)
			break ;
		trim_newline(ret);
		if (limiter_is_read(&flag, &ret, limiter))
			break ;
		if (is_var_heredoc(ret))
			ret = ft_replace_variable(ret, envp);
		ret = ft_strjoin(ret, "\n", SAFE);
		join = ft_strjoin(join, ret, SAFE);
	}
	heredoc_delimited_by_eof(flag, count, limiter);
	return (join);
}

int	ft_exec_pipe(t_asttree *node, t_hash *envp)
{
	int	flag;

	flag = 0;
	ft_exec_expand_redir(node, envp);
	if (flag)
	{
		hash_changevalue(&envp, "?", ft_itoa(flag, SAFE), CRITICAL);
		return (130);
	}
	return (ft_exec_pipeline(node, envp));
}
