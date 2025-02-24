/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:58 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:12:01 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <dirent.h>
#include <stdbool.h>

char	**get_file_list_malloc(char *s)
{
	DIR				*dir;
	struct dirent	*entry;
	int				file_nb;
	char			**file_list;

	dir = opendir(".");
	if (!dir)
		perror("opendir");
	file_nb = 0;
	while (666)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..") && \
			match_wildcard(s, entry->d_name))
			file_nb++;
	}
	allocchk(file_list = walloc((file_nb + 1) * sizeof(char *), SAFE));
	file_list[file_nb] = NULL;
	file_list[0] = NULL;
	closedir(dir);
	return (file_list);
}

char	**get_wildcard_output(char *s)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			**file_list;

	file_list = get_file_list_malloc(s);
	dir = opendir(".");
	if (!dir)
		perror("opendir");
	i = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strcmp(entry->d_name, ".") && ft_strcmp(entry->d_name, "..") && \
			match_wildcard(s, entry->d_name))
			allocchk(file_list[i++] = ft_strdup(entry->d_name, SAFE));
	}
	closedir(dir);
	if (file_list[0] == NULL)
		return (NULL);
	else
		return (file_list);
}

char	**look_for_wildcards(char *s)
{
	char	**file_list;
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			found = 1;
			file_list = get_wildcard_output(s);
			if (file_list)
				found = 1;
		}
		i++;
	}
	if (found == 0)
		return (NULL);
	else
		return (file_list);
}

// the loop adds new nodes to the lst containing the file names that are
// matched by the regex.
t_list	*look_for_wildcards_and_expand_if_found(t_list **lst, \
												t_list *tmp, \
												char **file_list)
{
	int		fl_height;
	t_list	*new_node;

	replace_1ascii_with_wildcard(&file_list);
	fl_height = ft_tabtabheigth(file_list);
	ft_sorttabtab(&file_list, 1, fl_height);
	while (fl_height > 0)
	{
		new_node = ft_lstnew(ft_strdup(file_list[fl_height - 1], \
					SAFE), STR_TYPE, SAFE);
		allocchk((void *)new_node);
		ft_lstadd_after(lst, new_node, tmp);
		fl_height--;
	}
	free_file_list(&file_list);
	return (new_node);
}

// prodecure for '*' and "*" ->
// they have been replaced by a 1 ascii by quote remover
// the * inside file names are then replaced by 1 ascii
// match wildcard then works as expected
// then the 1 are big replaced by * inside the token and the file name.
void	wildcards(t_list **lst)
{
	t_list	*tmp;
	char	**file_list;
	t_list	*new_node;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->data_type == STR_TYPE && !tmp->is_heredoc_next)
		{
			file_list = look_for_wildcards(tmp->content.str_val);
			if (file_list != NULL)
			{
				new_node = \
					look_for_wildcards_and_expand_if_found(lst, tmp, file_list);
				ft_lstdelone(lst, tmp);
				tmp = new_node;
			}
			else
				replace_1_with_wild_single(&tmp->content.str_val);
		}
		tmp = tmp->next;
	}
}
