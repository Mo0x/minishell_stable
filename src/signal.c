/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:57:38 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 15:57:40 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_interactive_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "^C\n", 3);
		g_signal_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signals_to_default(void)
{
	set_signals(SIGINT, SIG_DEFAULT, DFLAGS, NULL);
	set_signals(SIGQUIT, SIG_DEFAULT, DFLAGS, NULL);
}

void	set_interactive_signals(void)
{
	set_signals(SIGINT, SIG_CUSTOM, DFLAGS, &sigint_interactive_handler);
	set_signals(SIGQUIT, SIG_IGNORE, DFLAGS, NULL);
}

void	handler_listen_to_signum(int signum)
{
	g_signal_status = signum;
}

void	set_signals(int signum, int type, int flags, void (*handler)(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		error_exit("sigemtpyset error\n");
	sa.sa_flags = flags;
	if (type == SIG_CUSTOM)
		sa.sa_handler = handler;
	if (type == SIG_LISTEN)
		sa.sa_handler = handler_listen_to_signum;
	else if (type == SIG_DEFAULT)
		sa.sa_handler = SIG_DFL;
	else if (type == SIG_IGNORE)
		sa.sa_handler = SIG_IGN;
	if (sigaction(signum, &sa, NULL) == -1)
		error_exit("sigaction failed\n");
}
