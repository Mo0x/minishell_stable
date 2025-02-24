/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:36:59 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:37:00 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sigint_handler(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n", 1);
	g_signal_status = SIGINT;
}

void	heredoc_delimited_by_eof(int flag, int count, char *limiter)
{
	if (!flag)
	{
		ft_putstr_fd("\nwarning: here-document at line ", 2);
		ft_putnbr_fd(count, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("')\n", 2);
	}
}

void	init_heredoc(int *flag, int *count, char **ret)
{
	set_signals(SIGINT, SIG_CUSTOM, SA_SIGINFO, heredoc_sigint_handler);
	set_signals(SIGQUIT, SIG_IGNORE, DFLAGS, NULL);
	*flag = 0;
	*count = 0;
	*ret = NULL;
}

int	limiter_is_read(int *flag, char **ret, char *limiter)
{
	if (ret && !(ft_strcmp(*ret, limiter)))
	{
		*flag = 1;
		wfree(*ret);
		return (1);
	}
	return (0);
}

void	trim_newline(char *s)
{
	if (s && s[ft_strlen(s) - 1] == '\n')
		s[ft_strlen(s) - 1] = 0;
}
