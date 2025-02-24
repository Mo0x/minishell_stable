/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:37:12 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/07 17:38:46 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_limiter(char *ret, char *limiter, int *flag)
{
	if (ret && !(ft_strcmp(ret, limiter)))
	{
		*flag = 1;
		wfree(limiter);
		wfree(ret);
		return (1);
	}
	return (0);
}

char	*get_heredoc_line(void)
{
	write(STDOUT_FILENO, "> ", 2);
	return (get_next_line(STDIN_FILENO));
}

char	*change_ret_to_130_and_return_null(t_hash *envp)
{
	hash_changevalue(&envp, "?", ft_strdup("130", SAFE), CRITICAL);
	return (NULL);
}

void	put_line_to_superpipe(int super_pipe, char *ret, int *count)
{
	ft_putstr_fd(ret, super_pipe);
	ft_putstr_fd("\n", super_pipe);
	wfree(ret);
	(*count)++;
}

int	is_var_heredoc(char *s)
{
	char	*tmp;

	tmp = ft_strchr(s, '$');
	if (tmp && *(tmp + 1))
		return (1);
	return (0);
}
