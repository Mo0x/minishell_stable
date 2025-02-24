/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:49:48 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/11 18:22:31 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_asttree	*ft_nxt_cmd(t_asttree *node)
{
	if (node->children[1]->type == BUILTIN || node->children[1]->type == \
		COMMAND || node->children[1]->type == SUBTREE)
		return (node->children[1]);
	else
	{
		return (node->children[1]->children[0]);
	}
}

int	ft_and_routine1(int *exit_s, int pid, t_asttree *node, t_hash *envp)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (ft_errno_error("Ft_and waitpid error\n"));
	if (WIFEXITED(status))
	{
		node->children[0]->skip = 1;
		*exit_s = WEXITSTATUS(status);
		hash_changevalue(&envp, "?", ft_itoa(*exit_s, SAFE), CRITICAL);
		if (*exit_s != 0)
			(ft_nxt_cmd(node))->skip = 1;
		else if (ft_nxt_cmd(node)->type == SUBTREE)
			ft_exec_subtree(ft_nxt_cmd(node), envp);
		else
			return (*exit_s);
	}
	else
		return (-1);
	return (*exit_s);
}

int	ft_and_routine(t_asttree *node, t_hash *envp)
{
	pid_t	pid;
	int		status;
	int		exit_s;

	pid = fork();
	if (pid == -1)
		return (ft_errno_error("Ft_and error forking\n"));
	else if (!pid)
	{
		status = ft_executor(node->children[0], envp, 0);
		wclear(1);
		exit(status);
	}
	else
		return (ft_and_routine1(&exit_s, pid, node, envp));
	return (exit_s);
}

int	ft_and(t_asttree *node, t_hash *envp)
{
	int	status;

	if (node->children[0]->type == BUILTIN || node->children[0]->type == \
		AND_OP || node->children[0]->type == OR_OP || \
		node->children[0]->type == SUBTREE)
	{
		status = ft_executor(node->children[0], envp, 0);
		node->children[0]->skip = 1;
		hash_changevalue(&envp, "?", ft_itoa(status, SAFE), CRITICAL);
		if (status != 0)
			(ft_nxt_cmd(node))->skip = 1;
		else if (ft_nxt_cmd(node)->type == SUBTREE)
			ft_exec_subtree(ft_nxt_cmd(node), envp);
		else
			return (status);
		return (status);
	}
	else
		return (ft_and_routine(node, envp));
	return (status);
}

/* int	ft_or_routine(t_asttree *node, t_hash *envp)
{
	pid_t	pid;
	int		status;
	int		exit_s;

	pid = fork ();
	if (pid == -1)
		return (ft_errno_error("Ft_or error forking \n"));
	else if (!pid)
	{
		status = ft_executor(node->children[0], envp, 0);
		wclear(1);
		exit(status);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (ft_errno_error("ft_or waitpid error\n"));
		if (WIFEXITED(status))
		{
			node->children[0]->skip = 1;
			exit_s = WEXITSTATUS(status);
			hash_changevalue(&envp, "?", ft_itoa(exit_s, SAFE), CRITICAL);
			if (exit_s == 0)
				(ft_nxt_cmd(node))->skip = 1;
			else if (ft_nxt_cmd(node)->type == SUBTREE)
				ft_exec_subtree(ft_nxt_cmd(node), envp);
			else
				return (exit_s);
		}
		else
			return (-1);
	}
	return (exit_s);
}

int	ft_or(t_asttree *node, t_hash *envp)
{
	int	status;

	if (node->children[0]->type == BUILTIN || node->children[0]->type == AND_OP
	|| node->children[0]->type == OR_OP || node->children[0]->type == SUBTREE)
	{
		printf("Im here lol debuf \n\n\n");
		status = ft_executor(node->children[0], envp, 0);
		node->children[0]->skip = 1;
		hash_changevalue(&envp, "?", ft_itoa(status, SAFE), CRITICAL);
		if (status == 0)
			(ft_nxt_cmd(node))->skip = 1;
		else if (ft_nxt_cmd(node)->type == SUBTREE)
			ft_exec_subtree(ft_nxt_cmd(node), envp);
		else
			return (status);
		return (status);
	}
	else
		return (ft_or_routine(node, envp));
} */
