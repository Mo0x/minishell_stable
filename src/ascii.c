/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:55:50 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:33:23 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ascii(void)
{
	char	*cat;
	char	*param[3];
	pid_t	pid;
	int		sts_execve;

	cat = "/bin/cat";
	param[0] = "/bin/cat";
	param[1] = "./ascii";
	param[2] = NULL;
	sts_execve = 0;
	pid = fork();
	if (pid == -1)
		ft_errno_error("Error fork ft_ascii");
	else if (!pid)
	{
		sts_execve = execve(cat, param, NULL);
		if (sts_execve != 0)
			error_print("couldnt load ascii art :'(");
		exit(-1);
	}
	else
		wait(NULL);
	write(1, "\n", 1);
}
