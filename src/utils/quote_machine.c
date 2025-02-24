/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:32 by achatzit          #+#    #+#             */
/*   Updated: 2024/05/15 16:40:34 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_MACHINE_UPDATE_STATE 0
#define QUOTE_MACHINE_GET_STATE 1
#define QUOTE_MACHINE_RESET 2

int	quote_state_machine(char c, int type)
{
	static int	cur_quote;

	if (type == QUOTE_MACHINE_UPDATE_STATE)
	{
		if (!cur_quote && (c == 34 || c == 39))
			cur_quote = c;
		else if (cur_quote && c == cur_quote)
			cur_quote = 0;
	}
	else if (type == QUOTE_MACHINE_GET_STATE)
		return (cur_quote);
	else if (type == QUOTE_MACHINE_RESET)
		cur_quote = 0;
	return (-1);
}

void	qmachine_update(char c)
{
	(void)quote_state_machine(c, QUOTE_MACHINE_UPDATE_STATE);
}

int	qmachine_getstate(void)
{
	return (quote_state_machine(0, QUOTE_MACHINE_GET_STATE));
}

void	qmachine_reset(void)
{
	(void)quote_state_machine(0, QUOTE_MACHINE_RESET);
}
