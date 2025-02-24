/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:39:52 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:40:49 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_PATH 4098

/*
mgovinda@k2r3p5:~/minishell$ ln -s ~ .
mgovinda@k2r3p5:~/minishell$ ls -la
total 440
drwxr-xr-x  8 mgovinda 2023_mulhouse    185 avril  3 18:02 .
drwx------ 37 mgovinda 2023_mulhouse   4096 avril  3 18:00 ..
-rw-r--r--  1 mgovinda 2023_mulhouse    419 avril  3 17:27 ascii
drwxr-xr-x  8 mgovinda 2023_mulhouse    185 avril  3 17:33 .git
-rw-r--r--  1 mgovinda 2023_mulhouse     23 avril  3 17:27 .gitignore
drwxr-xr-x  2 mgovinda 2023_mulhouse    162 avril  3 17:27 includes
drwxr-xr-x  2 mgovinda 2023_mulhouse   4096 avril  3 17:27 libft
-rw-r--r--  1 mgovinda 2023_mulhouse    652 avril  3 17:27 Makefile
lrwxrwxrwx  1 mgovinda 2023_mulhouse     14 avril  3 18:02 mgovinda ->
	/home/mgovinda
-rwxr-xr-x  1 mgovinda 2023_mulhouse 419024 avril  3 17:40 minishell
drwxr-xr-x  3 mgovinda 2023_mulhouse     17 avril  3 17:37 objs
drwxr-xr-x  9 mgovinda 2023_mulhouse    139 avril  3 17:27 src
-rw-r--r--  1 mgovinda 2023_mulhouse    119 avril  3 17:27 suppression.vg
drwxr-xr-x  2 mgovinda 2023_mulhouse     19 avril  3 17:27 tests
mgovinda@k2r3p5:~/minishell$ pwd
/home/mgovinda/minishell
mgovinda@k2r3p5:~/minishell$ cd mgovinda
mgovinda@k2r3p5:~/minishell/mgovinda$ pwd
/home/mgovinda/minishell/mgovinda
mgovinda@k2r3p5:~/minishell/mgovinda$ cd mgovinda
bash: cd: mgovinda: No such file or directory
mgovinda@k2r3p5:~/minishell/mgovinda$ cd minishell
mgovinda@k2r3p5:~/minishell/mgovinda/minishell$ cd mgovinda
mgovinda@k2r3p5:~/minishell/mgovinda/minishell/mgovinda$

TODO ln -s

1 get the path, check if its absolute
1 bis split path
2 	1 count the number of dir pathing
	2 count the double dots
	3 check if one is a symlink
3 resolve symlink
4 do the change dir
5 update the oldpwd, with pwd
5bis if pwd unset use getcwd
6 update pwd by adding the pwd
7 if symlink keepp track of the depth inside the symlink

todo cd
creating directory trying to .. seg fault
abc symlink quit
TODO PERMISSION DENIed when at root
*/

int	is_absolute_path(const char *path)
{
	return (path[0] == '/');
}

char	*ft_cat_paths(const char *path1, const char *path2)
{
	char	*ret;

	ret = ft_strjoin(path1, "/", SAFE);
	ret = ft_strjoin(ret, path2, CRITICAL);
	return (ret);
}

char	*do_the_symlink(const char *path, t_hash *envp)
{
	char		*cwd;
	char		*ret;
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (NULL);
	if (S_ISLNK(st.st_mode))
	{
		cwd = ft_strdup(hash_getvalue(envp, "PWD"), CRITICAL);
		if (!cwd)
		{
			ft_errno_error("do_the_symlink getcwd");
			return (NULL);
		}
		if (is_absolute_path(path))
			ret = ft_strdup(path, CRITICAL);
		else
			ret = ft_cat_paths(cwd, path);
		wfree(cwd);
		if (DEBUG)
			printf("ret = %s\n", ret);
		return (ret);
	}
	return (ft_strdup(path, SAFE));
}

int	chdir_routine(char *path)
{
	if (chdir(path) == -1)
		return (-1);
	return (0);
}

int	count_the_simple_path(char **tmp_path)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (tmp_path[++i])
	{
		if (ft_strcmp(tmp_path[i], "..") == 0 && ret > 0
			&& ft_strcmp(tmp_path[ret - 1], "..") != 0)
			ret--;
		else if (ft_strcmp(tmp_path[i], ".") != 0 && ft_strcmp(tmp_path[i],
				"") != 0)
			ret++;
	}
	return (ret);
}

/* char	**do_the_simple_path(char *path)
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
		if (ft_strcmp(tmp_path[i], "..") == 0 && j > 0 && ft_strcmp(s_path[j
				- 1], "..") != 0)
			j--;
		else if (ft_strcmp(tmp_path[i], ".") != 0 && ft_strcmp(tmp_path[i],
				"") != 0)
		{
			s_path[j] = ft_strdup(tmp_path[i], SAFE);
			if (s_path[j] == NULL)
			{
				ft_eq("Error malloc do_the_simple_path");
				free(s_path);
				return (NULL);
			}
			j++;
		}
	}
	s_path[j] = NULL;
	ft_freetab((void **)tmp_path);
	if (DEBUG)
	{
		for (int k = 0; s_path[k]; k++)
			printf("s_path[%d] = %s\n", k, s_path[k]);
	}
	return (s_path);
} */

/* int	do_the_path_thing(char *path, t_hash *envp)
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
} */

/* int	do_the_doubledots_thing(t_hash *envp)
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
		return (-42); // TODO
	*tmp = 0;
	if (DEBUG)
		printf("tmp = %s\n", pwd);
	if (!ft_strcmp(pwd, ""))
		pwd = "/";
	if (chdir_routine(pwd) == -1)
		flag = ft_errno_error("do_the_doubledots_thing couldnt change dir");
	hash_changevalue(&envp, "PWD", ft_strdup(pwd, SAFE), CRITICAL);
	return (flag);
} */
/* TODO case where cd fail edit oldpwd and pwd to old value*/
/* void	revert_back(t_hash *envp, char **oldpwds)
{
	hash_changevalue(&envp, "OLDPWD", oldpwds[0], CRITICAL);
	hash_changevalue(&envp, "PWD", oldpwds[1], CRITICAL);
	chdir_routine(oldpwds[1]);
} */

/* int	b_cd(t_hash *envp, char *path)
{
	char	**s_path;
	int		i;
	int		flag;
	char	*oldpwds[2];

	flag = 0;
	i = 0;
	oldpwds[0] = ft_strdup(hash_getvalue(envp, "OLDPWD"), CRITICAL);
	oldpwds[1] = ft_strdup(hash_getvalue(envp, "PWD"), CRITICAL);
	if (is_absolute_path(path))
	{
		// TODO ROUTINE ABSOLUTE PATH
		if ((flag = chdir_routine(path)) != 0)
		{
			ft_errno_error("b_cd");
			revert_back(envp, oldpwds);
		}
		else
		{
			hash_changevalue(&envp, "OLDPWD", oldpwds[1], CRITICAL);
			hash_changevalue(&envp, "PWD", path, CRITICAL);
		}
		return (flag);
	}
	s_path = do_the_simple_path(path);
	while (s_path[i])
	{
		if (ft_strcmp(s_path[i], ".."))
			flag = do_the_path_thing(s_path[i], envp);
		else
		{
			if (!getcwd(NULL, 0))
				do_the_doubledots_thing(envp);
			else if (ft_strcmp(getcwd(NULL, 0), "/") != 0)
				flag = do_the_doubledots_thing(envp);
		}
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
} */
/* 
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

int	b_cd_init(t_hash *envp, char *path)
{
	char	*oldpwds[2];

	if (!path)
	{
		oldpwds[0] = hash_getvalue(envp, "HOME");
		oldpwds[1] = hash_getvalue(envp, "PWD");
		if (!oldpwds[0])
		{
			ft_putendl_fd("qweqweshell : HOME not set", 2);
			return (1);
		}
		hash_changevalue(&envp, "OLDPWD", oldpwds[1], CRITICAL);
		hash_changevalue(&envp, "PWD", oldpwds[0], CRITICAL);
		return (chdir_routine(oldpwds[0]));
	}
	path = is_root(path);
	if (ft_strcmp(path, "//") == 0)
	{
		oldpwds[0] = ft_strdup(hash_getvalue(envp, "OLDPWD"), CRITICAL);
		oldpwds[1] = ft_strdup(hash_getvalue(envp, "PWD"), CRITICAL);
		chdir_routine("//");
		hash_changevalue(&envp, "OLDPWD", oldpwds[1], CRITICAL);
		hash_changevalue(&envp, "PWD", "//", CRITICAL);
		return (0);
	}
	else
		return (b_cd(envp, path));
} */
