/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:41:49 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:43:08 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	b_cd1(t_hash *envp, char *path, char **oldpwds, int *flag)
{
	*flag = chdir_routine(path);
	if (*flag != 0)
	{
		ft_errno_error("b_cd");
		revert_back(envp, oldpwds);
	}
	else
	{
		hash_changevalue(&envp, "OLDPWD", oldpwds[1], CRITICAL);
		hash_changevalue(&envp, "PWD", path, CRITICAL);
	}
	return (*flag);
}

void	b_cd2(t_hash *envp, int *i, char **s_path, int *flag)
{
	char	*s;

	if (ft_strcmp(s_path[*i], ".."))
		*flag = do_the_path_thing(s_path[*i], envp);
	else
	{
		s = getcwd(NULL, 0);
		if (!s)
			do_the_doubledots_thing(envp);
		else if (ft_strcmp(s, "/") != 0)
			*flag = do_the_doubledots_thing(envp);
		free(s);
	}
}

int	b_cd(t_hash *envp, char *path)
{
	char	**s_path;
	int		i;
	int		flag;
	char	*oldpwds[2];

	flag = 0;
	i = 0;
	oldpwds[0] = ft_strdup(hash_getvalue(envp, "OLDPWD"), SAFE);
	oldpwds[1] = ft_strdup(hash_getvalue(envp, "PWD"), SAFE);
	if (is_absolute_path(path))
		return (b_cd1(envp, path, oldpwds, &flag));
	s_path = do_the_simple_path(path);
	while (s_path[i])
	{
		b_cd2(envp, &i, s_path, &flag);
		if (flag)
		{
			ft_errno_error("b_cd");
			revert_back(envp, oldpwds);
			return (flag);
		}
		i++;
	}
	hash_changevalue(&envp, "OLDPWD", oldpwds[1], CRITICAL);
	return (flag);
}

char	*is_root(char *path)
{
	int	i;

	i = 1;
	if (ft_strcmp("//", path) == 0)
		return (path);
	if (path[0] != '/')
		return (path);
	while (path[i])
	{
		if (path[i] != '/')
			return (path);
		i++;
	}
	return (ft_strdup("/", CRITICAL));
}
