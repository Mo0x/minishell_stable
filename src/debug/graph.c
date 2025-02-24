#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>

void generate_dot(FILE* file, t_asttree *node)
{
	if (node == NULL)
		return;

	fprintf(file, "\"%p\"", node);
	fprintf(file, "[");
	if (node->type == REDIRECTION || node->type == SUBTREE)
		fprintf(file, "fontsize=9 ");
	if (node->type != COMMAND && node->type != BUILTIN && node->type != REDIRECTION && node->type != SUBTREE)
		fprintf(file, "fontcolor=purple ");
	else if (node->type == COMMAND || node->type == BUILTIN)
		fprintf(file, "fontcolor=blue");
	else if (node->type == SUBTREE)
		fprintf(file, "fontcolor=red");
	fprintf(file," label=<");
	if (node->type != COMMAND && node->type != BUILTIN && node->type != REDIRECTION)
	{
		fprintf(file, "%s", convert_type(node->type));
	}
	else if (node->type == REDIRECTION)
	{
		if (!ft_strcmp(node->l_param->content.str_val, "<<"))
			fprintf(file, "HEREDOC<br/>");
		else if (!ft_strcmp(node->l_param->content.str_val, ">>"))
			fprintf(file, "APPEND REDIR<br/>");
		else if (!ft_strcmp(node->l_param->content.str_val, ">"))
			fprintf(file, "OUTPUT REDIR<br/>");
		else if (!ft_strcmp(node->l_param->content.str_val, "<"))
			fprintf(file, "INPUT REDIR<br/>");
		fprintf(file, "%s", node->l_param->next->content.str_val);
	}
	else if (node->type == COMMAND || node->type == BUILTIN)
	{
		t_list *tmp = node->l_param;
		int i = 0;
		while (tmp)
		{
			if (i == 3)
			{
				i = 0;
				fprintf(file, "<br/>");
			}
			fprintf(file, "%s ", tmp->content.str_val);
			tmp = tmp->next;
			i++;
		}
	}
	else if (node->type == VOID)
	{
		fprintf(file, "void ");
	}
	fprintf(file, ">");
	// fprintf(file, ""); //for additional stuff
	fprintf(file, "];\n");

	for (int i = 0; i < node->num_child; i++)
	{
		fprintf(file, "\"%p\" -> \"%p\";\n", node, node->children[i]);
		generate_dot(file, node->children[i]);
	}
}

void	graph(t_asttree *ast)
{
	FILE	*dotfile = fopen("asstree.dot", "w");
	if (!dotfile)
	{
		perror("error opening the dotfile");
		return ;
	}
	fprintf(dotfile, "digraph AST {\n");
	generate_dot(dotfile, ast);
	fprintf(dotfile, "}\n");
	fclose(dotfile);
}
