/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:56:57 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/13 18:27:55 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_fds *head)
{
	t_fds	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->fd)
			close(tmp->fd);
		tmp = tmp->next;
	}
}

void	add_back_fds(t_fds *dad, t_fds *child)
{
	if (!dad)
		return ;
	else
	{
		while (dad->next)
			dad = dad->next;
		dad->next = child;
	}
}

t_fds	*create_fd(int fd)
{
	t_fds	*new;

	new = walloc(sizeof(t_pipe), SAFE);
	if (!new)
		ft_eq("ERROR MALLOC create pipe");
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	fds(int fd, int new)
{
	t_fds			*tp;
	static t_fds	*head = NULL;

	if (fd < 0)
		return ;
	if (new == 1)
	{
		if (!head)
			head = create_fd(fd);
		else
		{
			tp = create_fd(fd);
			add_back_fds(head, tp);
		}
	}
	else
	{
		if (head)
			close_fds(head);
		head = NULL;
	}
}
