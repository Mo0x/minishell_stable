/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:54:21 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/15 17:14:54 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_builtin_cd(t_asttree *node, t_hash *envp, int *flag)
{
	if (node->param && node->param[1])
	{
		if (node->param[2] && node->param[2][0] != ' ')
		{
			hash_changevalue(&envp, "?", "1", CRITICAL);
			return (ft_error("qweqweshell: b_cd: too many argument"));
		}
	}
	*flag = b_cd_init(envp, node->param[1]);
	if (*flag)
		hash_changevalue(&envp, "?", "1", CRITICAL);
	return (*flag);
}

int	ft_exec_builtin(t_asttree *node, t_hash *envp)
{
	int	flag;

	flag = 0;
	ft_exec_expand_redir(node, envp);
	if (node->here_doc)
		ft_heredoc_init(node, envp);
	if (!(ft_strcmp(node->value, "cd")))
		return (ft_builtin_cd(node, envp, &flag));
	else if (!(ft_strcmp(node->value, "echo")))
		flag = b_echo(node->param, node->fdo);
	else if (!(ft_strcmp(node->value, "exit")))
		flag = b_exit(node, envp);
	else if (!(ft_strcmp(node->value, "env")))
		flag = b_env(envp, node->fdo);
	else if (!(ft_strcmp(node->value, "pwd")))
		flag = b_pwd(envp, node->fdo);
	else if (!(ft_strcmp(node->value, "export")))
		flag = b_export_init(envp, node->param, node->fdo);
	else if (!(ft_strcmp(node->value, "unset")))
		flag = b_unset(envp, node->param);
	if (flag < 0)
		flag = -flag;
	hash_changevalue(&envp, "?", ft_itoa(flag, SAFE), CRITICAL);
	return (flag);
}
