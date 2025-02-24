/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:03:15 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/11 18:18:57 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_asttree	*ft_lstpipedcmd(t_asttree *node)
{
	while (node->type == PIPE_OP)
		node = node->children[1];
	if (node->type == COMMAND || node->type == BUILTIN)
		return (node);
	else
		return (node->children[0]);
}

void	close_pipe(t_pipe *head)
{
	while (head)
	{
		close(head->entree);
		close(head->exit);
		head = head->next;
	}
}

int	ft_lstcmd1(t_asttree *node, t_hash *envp)
{
	if (node->type == VOID || node->type == REDIRECTION)
	{
		exit (0);
	}
	if (node->type == BUILTIN)
		ft_exec_builtin(node, envp);
	else
	{
		ft_exec_command(node, envp, 0);
		exit(-1);
	}
	node->skip = 1;
	exit(-1);
	return (0);
}

void	ft_lstcmd2(t_asttree *node, t_hash *envp, int forks, int *sts)
{
	int		i;
	int		lst_sts;
	pid_t	wpid;

	i = 0;
	node->skip = 1;
	pipe_handler(NULL, 0);
	while (i <= forks)
	{
		wpid = waitpid(-1, sts, 0);
		if (WIFEXITED(*sts))
		{
			lst_sts = WEXITSTATUS(*sts);
			hash_changevalue(&envp, "?", ft_itoa(lst_sts, SAFE), CRITICAL);
		}
		if (wpid < 1)
			break ;
		i++;
	}
}

int	ft_lstcmd(t_asttree *node, t_hash *envp, int forks)
{
	pid_t	pid;
	int		sts;
	int		lst_sts;

	sts = 0;
	pid = fork();
	if (pid == -1)
		ft_errno_error("Error while forking");
	if (!(pid))
		return (ft_lstcmd1(node, envp));
	else
	{
		ft_lstcmd2(node, envp, forks, &sts);
		waitpid(pid, &sts, 0);
		if (WIFEXITED(sts))
		{
			lst_sts = WEXITSTATUS(sts);
			hash_changevalue(&envp, "?", ft_itoa(lst_sts, SAFE), CRITICAL);
			return (lst_sts);
		}
		else
			return (-42);
	}
	return (0);
}
