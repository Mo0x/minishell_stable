/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:11:01 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/12 16:14:17 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	ft_exec_fork_child(t_asttree *node, t_hash *envp, int stdin, int stdout)
{
	if (node->here_doc)
		ft_heredoc_init(node, envp);
	if (dup2(node->fdi, STDIN_FILENO) == -1)
		ft_errno_error("dup2 error");
	ft_cmd_executor(node, envp, stdin, stdout);
}

int	ft_exec_fork(t_asttree *node, t_hash *envp, int stdin, int stdout)
{
	pid_t	pid;
	int		sts;

	pid = fork();
	if (pid == -1)
		ft_errno_error("Error fork, ft_execfork");
	else if (!pid)
		ft_exec_fork_child(node, envp, stdin, stdout);
	else
	{
		set_signals(SIGINT, SIG_IGNORE, DFLAGS, NULL);
		wait(&sts);
		if (WIFSIGNALED(sts))
			hash_changevalue(&envp, "?", ft_itoa2(128 + WTERMSIG(sts), SAFE), \
			CRITICAL);
		else
			hash_changevalue(&envp, "?", ft_itoa(WEXITSTATUS(sts), SAFE), \
			CRITICAL);
	}
	return (0);
}

void	ft_exec_command_fds(int stdout, int stdin)
{
	fds(stdout, 1);
	fds(stdin, 1);
}
