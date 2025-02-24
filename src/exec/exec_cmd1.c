/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:11:07 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/12 16:13:47 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_requalify(t_asttree *node)
{
	if (!ft_strcmp(node->value, "cd"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "echo"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "exit"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "env"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "pwd"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "export"))
		node->type = BUILTIN;
	else if (!ft_strcmp(node->value, "unset"))
		node->type = BUILTIN;
}

int	ft_exec_command1(t_asttree *node, t_hash *envp, int *flag)
{
	int	ret;

	ret = 0;
	ft_requalify(node);
	if (node->type == BUILTIN)
	{
		*flag = 1;
		return (ft_exec_builtin(node, envp));
	}
	if (node->fdi < 0 || node->fdo < 0)
		return (-1);
	if (node->to_close)
		close(node->to_close);
	if (dup2(node->fdi, STDIN_FILENO) == -1)
		ft_errno_error("dup2 error fdi");
	if ((dup2((node->fdo), STDOUT_FILENO)) == -1)
		ft_errno_error("dup2 error fdo");
	return (ret);
}

void	ft_exec_command2(t_asttree *node)
{
	int	pipev3[2];

	pipe(pipev3);
	ft_putstr_fd(node->stached_heredoc, pipev3[1]);
	if (dup2(pipev3[0], STDIN_FILENO) == -1)
		ft_errno_error("dup2 error fdi");
	fds(pipev3[0], 1);
	fds(pipev3[1], 1);
	close(pipev3[1]);
	wfree(node->stached_heredoc);
	node->here_doc = NULL;
}

void	ft_exec_command3(int stdout, int stdin)
{
	if (dup2(stdout, 1) == -1)
		ft_errno_error("dup2 error ft_exec_command");
	if (dup2(stdin, 0) == -1)
		ft_errno_error("dup2 error ft_exec_command");
}

int	ft_exec_command(t_asttree *node, t_hash *envp, int fork)
{
	int	ret;
	int	stdout;
	int	stdin;
	int	flag;

	flag = 0;
	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	ft_exec_command_fds(stdout, stdin);
	ret = 0;
	ft_exec_expand_redir(node, envp);
	if (node->value[0] == '$')
		if (node->param[1])
			node->value = node->param[1];
	ret = ft_exec_command1(node, envp, &flag);
	if (ret != 0 || flag != 0)
		return (ret);
	if (node->stached_heredoc)
		ft_exec_command2(node);
	if (fork)
		ret = ft_exec_fork(node, envp, stdin, stdout);
	else
		ret = ft_cmd_executor(node, envp, stdin, stdout);
	ft_exec_command3(stdout, stdin);
	return (ret);
}
