/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:52 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/16 14:56:15 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_signal_status;

void	transform_splitable_tabs_to_spaces(char *s)
{
	qmachine_reset();
	while (*s)
	{
		qmachine_update(*s);
		if (qmachine_getstate() == 0 && *s == '\t')
			*s = ' ';
		s++;
	}
}

t_hash	*init(char **argv, int argc, char **env, t_msh *msh)
{
	t_hash	*envp;

	(void)argv;
	(void)argc;
	set_env(msh, env);
	envp = msh->vars;
	rl_catch_signals = 0;
	ft_ascii();
	return (envp);
}

void	check_sigint(t_hash **envp)
{
	if (g_signal_status == 130)
		hash_changevalue(envp, "?", "130", CRITICAL);
	g_signal_status = 0;
}

// graph(tree);
int	parsing_and_execution(char *prompt, t_msh *msh, t_hash **envp)
{
	t_asttree	*tree;

	if (parser(prompt, msh) == FAILURE)
	{
		hash_changevalue(envp, "?", "2", CRITICAL);
		return (FAILURE);
	}
	if (has_parenthesis(msh->cmdlst.cmdlst))
		tree = setup_parenthesis_stuff(&msh->cmdlst.cmdlst);
	else
		tree = convert_list_to_asttree(msh, &msh->cmdlst.cmdlst, 0);
	asttree_preorder(tree, replace_silenced_metachars);
	asttree_preorder(tree, find_and_replace_lone_redirects);
	execution(tree, *envp);
	if (!ft_strcmp(hash_getvalue(*envp, "?"), "131"))
		write(1, "Quit\n", 5);
	return (0);
}

// allocator(0, PRINT_SIZE, NULL, 0);
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	t_msh	msh;
	t_hash	*envp;

	if (argc > 1)
		return (printf("executable arguments not supported\n"), 1);
	envp = init(argv, argc, env, &msh);
	while (1)
	{
		set_interactive_signals();
		prompt = readline("qweqwe-shell: ");
		if (!prompt)
			break ;
		check_sigint(&envp);
		if (prompt && *prompt && contains_nonblank_chars(prompt))
			add_history(prompt);
		transform_splitable_tabs_to_spaces(prompt);
		if (prompt && *prompt && contains_nonblank_chars(prompt))
			parsing_and_execution(prompt, &msh, &envp);
		fds(0, 0);
		wclear(0);
	}
	b_exit(NULL, envp);
}
