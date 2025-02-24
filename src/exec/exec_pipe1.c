/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:04:17 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 18:12:53 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_pipeline1(t_asttree *node, t_hash *envp, int *super_pipe)
{
	node->skip = 1;
	node->children[0]->to_close = super_pipe[0];
	node->children[0]->fdi = node->fdi;
	node->children[0]->fdo = super_pipe[1];
	node->children[1]->pid = node->pid;
	if (node->children[0]->type == COMMAND)
	{
		ft_exec_command(node->children[0], envp, 0);
	}
	else if (node->children[0]->type == BUILTIN)
		ft_exec_builtin(node->children[0], envp);
	wclear(0);
	exit(-1);
}

void	ft_exec_pipeline2(t_asttree *node, int *super_pipe)
{
	set_signals(SIGINT, SIG_IGNORE, DFLAGS, NULL);
	node->skip = 1;
	node->children[0]->skip = 1;
	node->children[1]->fdi = super_pipe[0];
	node->children[1]->fdo = node->fdo;
	close(super_pipe[1]);
}

void	ft_exec_pipeline3(t_asttree *node, int *super_pipe)
{
	(ft_lstpipedcmd(node))->fdi = super_pipe[0];
	(ft_lstpipedcmd(node))->fdo = node->fdo;
}

int	ft_exec_pipeline(t_asttree *node, t_hash *envp)
{
	int		super_pipe[2];
	pid_t	pid;
	int		forks;

	forks = 0;
	if (pipe(super_pipe) == -1)
		ft_eq("ft_exec_pipline");
	pipe_handler(super_pipe, 1);
	while (node->type == PIPE_OP)
	{
		if (pipe(super_pipe) == -1)
			ft_errno_error("Pipe creation failed");
		pipe_handler(super_pipe, 1);
		pid = fork();
		forks++;
		if (pid == -1)
			ft_errno_error("Error while forking");
		else if (!(pid))
			ft_exec_pipeline1(node, envp, super_pipe);
		else
			ft_exec_pipeline2(node, super_pipe);
		node = node->children[1];
	}
	ft_exec_pipeline3(node, super_pipe);
	return (ft_lstcmd(ft_lstpipedcmd(node), envp, forks));
}
