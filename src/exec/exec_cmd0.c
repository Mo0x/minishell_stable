/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:08:30 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 17:44:20 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**slasher(char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		if ((paths[i][ft_strlen(paths[i]) - 1]) != '/')
		{
			tmp = ft_strjoin(paths[i], "/", SAFE);
			if (!tmp)
				ft_eq("Couldn't join paths");
			wfree(paths[i]);
			paths[i] = tmp;
		}
		i++;
	}
	return (paths);
}

char	**ft_pathfinder(t_hash *envp)
{
	char	**paths;
	int		i;
	char	**env;

	i = 0;
	paths = NULL;
	env = env_conv(envp);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		env[i] = env[i] + 5;
		paths = ft_split(env[i], ':', SAFE);
		paths = slasher(paths);
	}
	return (paths);
}

char	*ft_cmdfinder(char **paths, char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	if (!paths)
		return (cmd);
	if (access(cmd, F_OK | X_OK) == 0 || cmd[0] == '.')
		return (cmd);
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], cmd, SAFE);
		if (!ret)
			ft_eq("ft_strjoin error");
		if (access(ret, F_OK | X_OK) == 0)
			return (ret);
		wfree(ret);
		i++;
	}
	return (NULL);
}

int	ft_cmd_executor(t_asttree *node, t_hash *envp, int stdin, int stdout)
{
	char	**paths;
	char	*ex;
	int		ret;

	ret = 0;
	paths = ft_pathfinder(envp);
	ex = ft_cmdfinder(paths, node->value);
	if (!ex || node->value[0] == 0)
	{
		ex = ft_cmd_notfound_error(node->value, stdin, stdout);
		perror(ex);
		wfree(ex);
		wclear(1);
		exit(127);
	}
	set_signals_to_default();
	if ((execve(ex, node->param, env_conv(envp)) == -1))
		ret = ft_errno_error("Exec fail");
	wclear(1);
	exit(-1);
	return (ret);
}
/* 
void	ft_exec_fork_child(t_asttree *node, t_hash *envp)
{
	if (node->here_doc)
		ft_heredoc_init(node, envp);
	if (dup2(node->fdi, STDIN_FILENO) == -1)
		ft_errno_error("dup2 error");
	ft_cmd_executor(node, envp);
}

int	ft_exec_fork(t_asttree *node, t_hash *envp)
{
	pid_t	pid;
	int		sts;
	int		lst_sts;

	pid = fork();
	if (pid == -1)
		ft_errno_error("Error fork, ft_execfork");
	else if (!pid)
		ft_exec_fork_child(node, envp);
	else
	{
		set_signals(SIGINT, SIG_IGNORE, DFLAGS, NULL);
		wait(&sts);
		if (WIFEXITED(sts))
		{
			lst_sts = WEXITSTATUS(sts);
			hash_changevalue(&envp, "?", ft_itoa(lst_sts, SAFE), CRITICAL);
			return (0);
		}
		else
			return (-42);
	}
	return (0);
} */
/* 
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
	fds(stdout, 1);
	ret = 0;
	ft_exec_expand_redir(node, envp);
	if (node->value[0] == '$')
		return (0);
	ret = ft_exec_command1(node, envp, &flag);
	if (ret != 0 || flag != 0)
		return (ret);
	if (node->stached_heredoc)
		ft_exec_command2(node);
	if (fork)
		ret = ft_exec_fork(node, envp);
	else
		ret = ft_cmd_executor(node, envp);
	ft_exec_command3(stdout, stdin);
	return (ret);
} */
