/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:41:57 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:42:24 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_the_simple_path2(char **s_path, char **tmp_path, int *i, int *j)
{
	s_path[*j] = ft_strdup(tmp_path[*i], SAFE);
	if (s_path[*j] == NULL)
	{
		ft_eq("Error malloc do_the_simple_path");
		wfree(s_path);
		return ;
	}
	(*j)++;
}

char	**do_the_simple_path(char *path)
{
	char	**tmp_path;
	char	**s_path;
	int		i;
	int		j;

	tmp_path = ft_split(path, '/', SAFE);
	s_path = (char **)walloc(sizeof(char *) * (count_the_simple_path(tmp_path)
				+ 1), SAFE);
	if (!s_path)
		ft_eq("malloc do_the_simple_path");
	i = -1;
	j = 0;
	while (tmp_path[++i])
	{
		if (ft_strcmp(tmp_path[i], "..") == 0 && j > 0 && ft_strcmp(s_path[j \
			- 1], "..") != 0)
			j--;
		else if (ft_strcmp(tmp_path[i], ".") != 0 && ft_strcmp(tmp_path[i],
				"") != 0)
			do_the_simple_path2(s_path, tmp_path, &i, &j);
	}
	s_path[j] = NULL;
	ft_freetab((void **)tmp_path);
	return (s_path);
}

int	do_the_path_thing(char *path, t_hash *envp)
{
	char	*pwd;
	char	*proper_path;
	int		flag;

	flag = 0;
	proper_path = do_the_symlink(path, envp);
	if (!proper_path)
	{
		return (-1);
	}
	if (is_absolute_path(proper_path))
	{
		flag = chdir_routine(proper_path);
		hash_changevalue(&envp, "PWD", ft_strdup(proper_path, CRITICAL),
			CRITICAL);
		return (flag);
	}
	flag = chdir_routine(proper_path);
	pwd = hash_getvalue(envp, "PWD");
	if (!(pwd[ft_strlen(pwd) - 1] == '/'))
		pwd = ft_strjoin(pwd, "/", SAFE);
	pwd = ft_strjoin(pwd, proper_path, SAFE);
	hash_changevalue(&envp, "PWD", ft_strdup(pwd, CRITICAL), CRITICAL);
	return (flag);
}

int	do_the_doubledots_thing(t_hash *envp)
{
	char	*pwd;
	int		flag;
	char	*tmp;

	pwd = hash_getvalue(envp, "PWD");
	flag = 0;
	if (!pwd)
		return (-1);
	tmp = ft_strrchr(pwd, '/');
	if (!tmp)
		return (-42);
	*tmp = 0;
	if (DEBUG)
		printf("tmp = %s\n", pwd);
	if (!ft_strcmp(pwd, ""))
		pwd = "/";
	if (chdir_routine(pwd) == -1)
		flag = ft_errno_error("do_the_doubledots_thing couldnt change dir");
	hash_changevalue(&envp, "PWD", ft_strdup(pwd, SAFE), CRITICAL);
	return (flag);
}

void	revert_back(t_hash *envp, char **oldpwds)
{
	hash_changevalue(&envp, "OLDPWD", oldpwds[0], CRITICAL);
	hash_changevalue(&envp, "PWD", oldpwds[1], CRITICAL);
	chdir_routine(oldpwds[1]);
}
