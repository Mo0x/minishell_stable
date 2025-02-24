/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:56:15 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/05 19:22:23 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_eq(char *msg)
{
	ft_putendl_fd(msg, 2);
	wclear(1);
	exit(-1);
}

int	ft_errno_error(char *str)
{
	perror(str);
	return (-1);
}

int	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (-1);
}

char	*ft_cmd_notfound_error(char *cmd, int stdin, int stdout)
{
	char	*ret;
	char	*ret1;
	char	*part1;
	char	*part2;

	part1 = "Command '";
	part2 = "' not found";
	ret1 = ft_strjoin(part1, cmd, SAFE);
	if (!ret1)
		ft_eq("Error malloc ft_cmd_notfound_error");
	ret = ft_strjoin(ret1, part2, SAFE);
	if (!ret)
		ft_eq("Error malloc ft_cmd_notfound_error");
	close(stdin);
	close(stdout);
	wfree(ret1);
	return (ret);
}
