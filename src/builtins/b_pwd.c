/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:37:40 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/30 18:43:06 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	b_pwd(t_hash *envp, int fd)
{
	char	*pwd_value;
	int		flag;

	flag = 0;
	pwd_value = hash_getvalue(envp, "PWD");
	if (!pwd_value)
		pwd_value = getcwd(NULL, 0);
	if (flag > -1)
		flag = write(fd, pwd_value, ft_strlen(pwd_value));
	if (flag > -1)
		flag = write(fd, "\n", 1);
	if (flag < 0)
		ft_errno_error("b_pwd");
	return (0);
}

/*int	b_pwd(t_hash *envp)
{
	char	*pwd_value;;

// todo check retour de write
	pwd_value = getcwd(NULL, 0);
	(void) envp;
	printf("%s\n", pwd_value);

	pwd_value = hash_getvalue(envp, "PWD");
	if (!pwd_value)
		return (FAILURE);
	printf("%s\n", pwd_value);
	return (SUCCESS);
}*/
