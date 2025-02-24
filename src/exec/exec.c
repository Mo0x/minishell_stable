/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:39:50 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 18:25:10 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_executor(t_asttree *node, t_hash *envp, int fork)
{
	if (node->skip == 1 || (node->skip && node->type != VOID))
		return (ft_atoi(hash_getvalue(envp, "?")));
	if (!node)
		return (0);
	if (node->type == BUILTIN)
		return (ft_exec_builtin(node, envp));
	else if (node->type == COMMAND)
		return (ft_exec_command(node, envp, fork));
	else if (node->type == PIPE_OP)
		return (ft_exec_pipe(node, envp));
	else if (node->type == AND_OP)
		return (ft_and(node, envp));
	else if (node->type == OR_OP)
		return (ft_or(node, envp));
	else if (node->type == SUBTREE)
		return (ft_exec_subtree(node, envp));
	else if (node->type == VOID)
		return (ft_void(node, envp));
	else
		return (0);
}

int	ft_exec(t_asttree *node, t_hash *envp)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (node == NULL)
		return (-1);
	flag = ft_executor(node, envp, 1);
	if (flag == 130)
		return (130);
	while (++i < node->num_child)
	{
		if (node->children[i]->type == SUBTREE)
			continue ;
		flag = ft_exec(node->children[i], envp);
	}
	flag = ft_atoi(hash_getvalue(envp, "?"));
	return (flag);
}

int	ft_exec_expand_redir(t_asttree *node, t_hash *envp)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	if (node->l_param)
		ft_param_expander(node, envp);
	if (node == NULL)
		return (-1);
	flag = ft_redir_init(node, envp);
	if (flag)
		return (flag);
	while (++i < node->num_child)
	{
		if (flag)
			break ;
		flag = ft_exec_expand_redir(node->children[i], envp);
	}
	return (flag);
}

void	get_sts(t_hash *envp)
{
	int	status;
	int	lst_sts;

	if (WIFEXITED(status))
	{
		lst_sts = WEXITSTATUS(status);
		if (DEBUG)
			printf("%d\n\n", lst_sts);
		hash_changevalue(&envp, "?", ft_itoa(lst_sts, SAFE), CRITICAL);
	}
}

void	execution(t_asttree *node, t_hash *envp)
{
	int	i;

	i = 0;
	if (node->type == VOID)
	{
		ft_redir_solo(node, envp);
		while (i < node->num_child)
		{
			ft_redir_solo(node->children[i], envp);
			i++;
			if (g_signal_status == SIGINT)
				return ;
		}
		return ;
	}
	else
		if (ft_exec_heredoc(node, envp) == 130)
			return ;
	ft_exec(node, envp);
	fds(0, 0);
	pipe_handler(0, 0);
}
