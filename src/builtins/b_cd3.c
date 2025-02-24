/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:35:29 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/29 23:39:28 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	b_cd_init1(t_hash *envp, char **oldpwds)
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

int	b_cd_init(t_hash *envp, char *path)
{
	char	*oldpwds[2];

	if (!path)
		return (b_cd_init1(envp, oldpwds));
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
}
