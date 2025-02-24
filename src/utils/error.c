/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:53 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:40:56 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_print(char *f, ...)
{
	va_list	arg;

	va_start(arg, f);
	while (*f)
	{
		if (*f == '%' && *(f + 1) && *(f + 1) == 's')
		{
			ft_putstr_fd(va_arg(arg, char *), 2);
			f += 2;
		}
		else
		{
			ft_putchar_fd(*f, 2);
			f++;
		}
	}
	va_end(arg);
}

void	error_exit(char *error_str)
{
	printf("%s\n", error_str);
	wclear(1);
	exit(EXIT_FAILURE);
}

void	allocchk(void *ptr)
{
	if (!ptr)
		error_exit("MALLOC FAILED allocchk\n");
}
