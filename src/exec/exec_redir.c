/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:26:39 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 16:07:48 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

/*
			cmd
			 |
			 |
			 |
			 redir
			 param1 = > OR >> OR <<
			 param2 = file, heredoc etc ...

must check before exec so do a exec init;
*/

int	ft_file_opener(char *path, int flag)
{
	int	ret;

	if (!flag)
	{
		if (access(path, F_OK | R_OK) == 0)
			ret = open(path, O_RDONLY);
		else
			return (ft_errno_error("File opener error, no access"));
	}
	else if (flag == 1)
		ret = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		ret = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	fds(ret, 1);
	return (ret);
}

int	ft_redir_fdo(t_asttree *node, int flag)
{
	node->skip = 1;
	if (flag)
		node->parent->fdo = ft_file_opener(node->param[1], 1);
	else
		node->parent->fdo = ft_file_opener(node->param[1], 2);
	if (node->parent->fdo < 0)
	{
		ft_errno_error("Error opening file");
		return (-1);
	}
	return (0);
}

int	ft_redir_fdi(t_asttree *node, int flag, t_hash *envp)
{
	(void) envp;
	node->skip = 1;
	if (flag)
		node->parent->fdi = ft_file_opener(node->param[1], 0);
	else
		node->parent->here_doc = node->param[1];
	if (node->parent->fdi < 0)
	{
		ft_errno_error("Error ft_redir_fdi");
		return (-1);
	}
	return (0);
}

int	ft_redir_init(t_asttree *node, t_hash *envp)
{
	if (node->type == REDIRECTION)
	{
		if (!(ft_strcmp(node->value, ">")))
			return (ft_redir_fdo(node, 1));
		else if (!(ft_strcmp(node->value, ">>")))
			return (ft_redir_fdo(node, 0));
		else if (!(ft_strcmp(node->value, "<")))
			return (ft_redir_fdi(node, 1, envp));
	}
	return (0);
}

int	ft_redir_solo(t_asttree *node, t_hash *envp)
{
	int	ret;

	(void)envp;
	if (node->type == REDIRECTION)
	{
		if (!(ft_strcmp(node->value, "<")))
			ret = ft_file_opener(node->l_param->next->content.str_val, 0);
		else if (!(ft_strcmp(node->value, "<<")))
			ret = ft_heredoc_solo(node->l_param->next->content.str_val, envp);
		else if (!(ft_strcmp(node->value, ">")))
			ret = ft_file_opener(node->l_param->next->content.str_val, 1);
		else if (!(ft_strcmp(node->value, ">>")))
			ret = ft_file_opener(node->l_param->next->content.str_val, 2);
		node->skip = 1;
	}
	return (ret);
}
