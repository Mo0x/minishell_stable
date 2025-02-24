/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatzit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:11:22 by achatzit          #+#    #+#             */
/*   Updated: 2024/03/07 17:11:26 by achatzit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*generate_lst_from_prompt_split(char *prompt)
{
	t_list	*lst;
	t_list	*p_s;
	t_list	*ps_tmp;
	int		token;
	t_list	*new;

	lst = NULL;
	allocchk(p_s = ft_split_lst(prompt, ' ', SAFE));
	replace_1_with_space_lst(p_s);
	while (p_s)
	{
		ps_tmp = p_s->next;
		token = get_single_token(p_s->content.str_val);
		if (token == FAILURE)
			allocchk(new = ft_lstnew(p_s->content.str_val, STR_TYPE, SAFE));
		else
		{
			allocchk(new = ft_lstnew(&token, INT_TYPE, SAFE));
			wfree(p_s->content.str_val);
		}
		ft_lstadd_back(&lst, new);
		wfree(p_s);
		p_s = ps_tmp;
	}
	return (lst);
}

t_list	*tokenize(char *prompt, t_msh *msh)
{
	t_list	*lst;

	if (check_pairs(prompt, msh) != SUCCESS)
		return (NULL);
	prompt = (silence_metachars_in_quotes(prompt));
	setup_quotes(prompt);
	lst = generate_lst_from_prompt_split(prompt);
	split_tokens_inside_strtypes(&lst);
	defragment_lst(&lst);
	add_void_nodes_before_lone_redirects(&lst);
	return (lst);
}
