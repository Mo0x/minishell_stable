/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:20:47 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/09 19:03:44 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	TODO heredoc "<<EOF solo"
	+ bash: warning: here-document at line 1
	delimited by end-of-file (wanted `EOF')
*/

int	ft_heredoc_solo(char *limiter, t_hash *envp)
{
	char	*ret;
	int		flag;
	int		count;

	init_heredoc(&flag, &count, &ret);
	if (!ft_strcmp(limiter, "\"\""))
		limiter = "";
	while (1)
	{
		ret = get_heredoc_line();
		if (g_signal_status == SIGINT)
		{
			hash_changevalue(&envp, "?", ft_strdup("130", SAFE), CRITICAL);
			return (130);
		}
		if (!ret)
			break ;
		trim_newline(ret);
		if (read_limiter(ret, limiter, &flag))
			break ;
		count++;
		wfree(ret);
	}
	heredoc_delimited_by_eof(flag, count, limiter);
	return (0);
}

int	ft_heredoc_stdin(char *limiter, int super_pipe, t_hash *envp)
{
	char	*ret;
	int		flag;
	int		count;

	if (!ft_strcmp(limiter, "\"\""))
		limiter = "";
	init_heredoc(&flag, &count, &ret);
	while (1)
	{
		ret = get_heredoc_line();
		if (g_signal_status == SIGINT)
			return (130);
		if (!ret)
			break ;
		trim_newline(ret);
		if (read_limiter(ret, limiter, &flag))
			break ;
		if (is_var_heredoc(ret))
			ret = ft_replace_variable(ret, envp);
		put_line_to_superpipe(super_pipe, ret, &count);
	}
	heredoc_delimited_by_eof(flag, count, limiter);
	return (0);
}

int	ft_heredoc_child(char *limiter, int *super_pipe, t_hash *envp)
{
	int	ret;

	close(super_pipe[0]);
	ret = ft_heredoc_stdin(limiter, super_pipe[1], envp);
	close(super_pipe[1]);
	exit(ret);
}

int	ft_heredoc_parent(t_asttree *node, int *super_pipe)
{
	int	sts;
	int	last_sts;

	last_sts = 0;
	close(super_pipe[1]);
	node->fdi = super_pipe[0];
	wait(&sts);
	if (WIFEXITED(sts))
	{
		last_sts = WEXITSTATUS(sts);
		if (last_sts == 130 && node->parent)
			node->parent->skip = 1;
	}
	return (last_sts);
}

int	ft_heredoc_init(t_asttree *node, t_hash *envp)
{
	int		super_pipe[2];
	pid_t	pid;
	int		ret;

	ret = 0;
	if (pipe(super_pipe) == -1)
		return (ft_errno_error("Pipe creation error, ft_heredoc_init"));
	fds(super_pipe[0], 1);
	fds(super_pipe[1], 1);
	pid = fork();
	if (pid == -1)
		return (ft_errno_error("Forking error, ft_heredo_init"));
	if (!pid)
	{
		ret = ft_heredoc_child(node->here_doc, super_pipe, envp);
	}
	else
	{
		set_signals(SIGINT, SIG_IGNORE, DFLAGS, NULL);
		set_signals(SIGQUIT, SIG_IGNORE, DFLAGS, NULL);
		ret = ft_heredoc_parent(node, super_pipe);
		hash_changevalue(&envp, "?", ft_itoa(ret, SAFE), CRITICAL);
	}
	return (ret);
}
