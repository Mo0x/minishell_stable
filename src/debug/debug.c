#include "../../includes/minishell.h"
#include <string.h>

void asttree_expand_tree(t_asttree *node)
{
	int	i;
	t_list	*tmp;

	i = -1;
	if(node)
	{
		printf("SKIP == %d\n", node->skip);
		printf("type = %d %s \n", node->type, convert_type(node->type));
		printf("value = %s \n", node->value);
		while (++i < ft_count_param(node->param))
			printf("param[%d] = %s\n", i, node->param[i]);
		printf("num children = %d \n", node->num_child);
		printf("here_doc = %s\n", node->here_doc);
		printf("stached here_doc %s\n", node->stached_heredoc);
		printf("fdi = %d\n", node->fdi);
		printf("fdo = %d\n", node->fdo);
		printf("pid = %d\n", node->pid);
		if (node->l_param)
		{
			int j = 0;
			tmp = node->l_param;
			if (node->l_param->data_type == STR_TYPE)
				printf("lparam %d == %s", j, tmp->content.str_val);
			tmp = tmp->next;
		}
		if (!node->l_param && (node->type != SUBTREE || node->type != TMP_SUBTREE))
			printf("index = %d\n", node->index);
		if (node->parent)
			printf("parent id : %d\n", node->parent->index);
		print_token_lst(node->l_param);
	}
}

void	print_prompt_split(char *prompt)
{
	t_list	*lst;
	t_list	*tmp;

	lst = ft_split_lst(prompt, ' ', SAFE);
	if (!lst)
		error_exit("MALLOC FAILED\n");
	printf("\nprompt split : \n\n");
	tmp = lst;
	while (lst)
	{
		printf("%s\n", (char *)lst->content.str_val);
		lst = lst->next;
	}
	printf("\n");
	free_lst(&tmp);
}

void	print_token_lst(t_list *lst)
{
	printf("\ntoken split : \n\n");
	while (lst)
	{
		if (lst->data_type == INT_TYPE)
				switch (lst->content.int_val) 
				{
					case PIPE:
						printf("%spiped into %s\n", BMAG, CRESET);
						break;
					case LESS:
						printf("%sninput redirection %s\n", BMAG, CRESET);
						break;
					case GREAT:
						printf("%soutput redirection\n%s", BMAG, CRESET);
						break;
					case DLESS:
						printf("%shere document ?\n%s", BMAG, CRESET);
						break;
					case DGREAT:
						printf("%sappend output redirection \n%s", BMAG, CRESET);
						break;
					case AND:
						printf("%sand \n%s", BMAG, CRESET);
						break;
					case OR:
						printf("%sor \n%s", BMAG, CRESET);
						break;
					case OPENP:
						printf("%sopen parenthesis \n%s", BMAG, CRESET);
						break;
					case CLOSEP:
						printf("%sclosing parenthesis \n%s", BMAG, CRESET);
						break;
				}
		else if (lst->data_type == STR_TYPE)
		{
			char voidness[] = {-6, -6, -6, 0};
			if (!memcmp(voidness, lst->content.str_val, strlen(lst->content.str_val)))
				printf("voiiiiiid\n");
			else
				printf("%s\n", lst->content.str_val);
		}
		lst = lst->next;
	}
	printf("\n");
}

void	print_commands(t_cmdlst *cmdlst)
{
	t_list	*lst = cmdlst->cmdlst;
	char voidness[] = {-6, -6, -6, 0};
	// int len = ft_lstsize(lst);
	
	// printf("\ncommands : \n\n");
	while (lst)
	{
		if (lst->data_type == STR_TYPE)
		{
			if (!lst->content.str_val[0])
			{
				printf("found empty string\n");
			}
			printf("%sbin : %s%s",BCYN, CRESET, lst->content.str_val);
		}
		lst = lst->next;
		if (lst && lst->data_type == STR_TYPE)
		{
			if (!ft_strcmp(voidness, lst->content.str_val))
			{
				printf("voiiiid\n");
				lst = lst->next;
				continue ;
			}
			printf("%s with args : %s", BCYN, CRESET);
			while (lst && lst->data_type == STR_TYPE)
			{
				printf("%s ", lst->content.str_val);
				lst = lst->next;
			}
		}
		if (lst && lst->data_type == INT_TYPE)
		{
			while (lst && lst->data_type == INT_TYPE)
			{
				switch (lst->content.int_val) 
				{
					case PIPE:
						printf("\npiped into ");
						break;
					case LESS:
						printf("\ninput redirection ");
						break;
					case GREAT:
						printf("\noutput redirection ");
						break;
					case DLESS:
						printf("\nhere document ?");
						break;
					case DGREAT:
						printf("\nappend output redirection ");
						break;
					case AND:
						printf("\nand ");
						break;
					case OR:
						printf("\nor ");
						break;
					case OPENP:
						printf("\nopen parenthesis ");
						break;
					case CLOSEP:
						printf("\nclosing parenthesis ");
						break;
				}
				lst = lst->next;
			}
		}
		printf("\n");
	}
}

void	print_pairs(t_pairs pairs)
{
	printf("\npairs : \n\n");
	printf("squotes %d\ndquotes %d\nopen pars %d\nclose pars %d\n\n", pairs.squote, pairs.dquote, pairs.open_par, pairs.close_par);
}

void	print_vars(t_msh msh)
{
	t_hash	*tmp;

	tmp = msh.vars;
	printf("\n variables : \n");
	while (tmp)
	{
		printf("key :   %s\nvalue : %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_logicaltree(t_asttree **tree)
{
	int	i = 0;
	
	t_asttree *lol;
	printf("logcical tree : \n\n");
	while ((lol = tree[i]) != NULL)
	{
		printf("%s", BBLU);
		asttree_expand_tree(lol);
		printf("%s", CRESET);
		printf("\n\n");
		i++;
	}
}

void	print_par_infos(t_par_depthsplit **pardsplit)
{

	int	i = 0;
	t_list	*tmp;

	while (pardsplit[i])
	{
		printf("%d (depth %d) : \n", i, pardsplit[i]->depth);
		tmp = pardsplit[i]->lst;
		while (tmp)
		{
			if (tmp->data_type == STR_TYPE)
			{
				printf("value : %s index : %d depth : %d group : %d\n", tmp->content.str_val, tmp->index, tmp->depth, tmp->par_group_index);
			}
			else if (tmp->data_type == INT_TYPE)
			{
					printf("INTTYPE, index :  %d, depth : %d group : %d\n", tmp->index, tmp->depth, tmp->par_group_index);
			}
			tmp = tmp->next;
		}
		i++;
	}
}
