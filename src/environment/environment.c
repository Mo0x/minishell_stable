/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:15:19 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 16:15:20 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

char	*get_envp_key(char *envp)
{
	char	*key;
	int		size;

	size = 0;
	key = NULL;
	while (envp[size] != '=')
		size++;
	allocchk(key = ft_substr(envp, 0, size, CRITICAL));
	return (key);
}

char	*get_envp_value(char *envp)
{
	char	*value;

	while (*envp != '=')
		envp++;
	envp++;
	allocchk(value = ft_substr(envp, 0, ft_strlen(envp), CRITICAL));
	return (value);
}

void	set_default_values_to_critical_vars_if_not_set(t_hash **envp)
{
	char	pwd[4096];

	if (!hash_getvalue(*envp, "OLDPWD"))
		hash_addback(envp, hashnew("OLDPWD", "", CRITICAL));
	if (!hash_getvalue(*envp, "PWD"))
	{
		if (!getcwd(pwd, 4096))
		{
			error_print("getcwd:\n%s\n", strerror(errno));
			error_exit("Exiting\n");
		}
		hash_addback(envp, hashnew("PWD", pwd, CRITICAL));
	}
	if (!hash_getvalue(*envp, "PATH"))
		hash_addback(envp, hashnew("PATH", \
	"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", CRITICAL));
	if (!hash_getvalue(*envp, "SHLVL"))
		hash_addback(envp, hashnew("SHLVL", "1", CRITICAL));
}

char	**env_conv(t_hash *vars)
{
	char	**env;
	char	*buf;
	int		i;

	i = 0;
	allocchk(env = walloc((hash_size(vars) + 1) \
						* sizeof (char *), SAFE));
	while (vars)
	{
		allocchk(env[i] = ft_strdup(vars->key, SAFE));
		buf = env[i];
		allocchk(env[i] = ft_strjoin(env[i], "=", SAFE));
		wfree(buf);
		buf = env[i];
		allocchk(env[i] = ft_strjoin(env[i], vars->value, SAFE));
		wfree(buf);
		i++;
		vars = vars->next;
	}
	env[i] = NULL;
	return (env);
}

void	set_env(t_msh *msh, char **envp)
{
	t_hash	*new;
	int		new_shlvl;

	msh->vars = NULL;
	while (*envp)
	{
		allocchk(new = hashnew(get_envp_key(*envp), \
					get_envp_value(*envp), CRITICAL));
		if (!ft_strcmp(new->key, "SHLVL"))
		{
			new_shlvl = ft_atoi(new->value);
			new_shlvl++;
			wfree(new->value);
			allocchk(new->value = ft_itoa2(new_shlvl, CRITICAL));
			if (DEBUG)
				printf("new shlvl : %s\n", new->value);
		}
		hash_addback(&msh->vars, new);
		envp++;
	}
	new = hashnew("?", "0", CRITICAL);
	hash_addback(&msh->vars, new);
	set_default_values_to_critical_vars_if_not_set(&msh->vars);
}
