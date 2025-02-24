/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:12:21 by achatzit          #+#    #+#             */
/*   Updated: 2024/06/13 18:13:39 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cmd_exists1(char ***paths, char **part_path, char **cmd, int i)
{
	char	*ret;

	*part_path = ft_strjoin(*(paths[i]), "/", SAFE);
	ret = ft_strjoin(*part_path, *cmd, SAFE);
	wfree(part_path);
	return (ret);
}

char	*cmd_exists(char *cmd, t_hash *envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;
	char	**env;

	env = env_conv(envp);
	i = -1;
	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':', SAFE);
	i = -1;
	while (paths[++i])
	{
		path = cmd_exists1(&paths, &part_path, &cmd, i);
		if (access(path, F_OK) == 0)
			return (path);
		wfree(path);
	}
	i = -1;
	while (paths[++i])
		wfree(paths[i]);
	wfree(paths);
	return (NULL);
}
