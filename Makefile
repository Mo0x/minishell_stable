NAME = minishell

SRC = src/ascii.c \
	src/signal.c \
	src/minishell.c \
	src/lst_asttree_converter/list_to_asttree/converter_join_child_with_parents.c \
	src/lst_asttree_converter/list_to_asttree/converter_utils.c \
	src/lst_asttree_converter/list_to_asttree/converter_get_command_as_asttree.c \
	src/lst_asttree_converter/list_to_asttree/converter_get_logical_nodes_tab.c \
	src/lst_asttree_converter/list_to_asttree/converter_join_with_parenthesis.c \
	src/lst_asttree_converter/list_to_asttree/converter_get_command_node_tab.c \
	src/lst_asttree_converter/list_to_asttree/converter_split_lst_at_redirection2.c \
	src/lst_asttree_converter/list_to_asttree/converter_join_no_parenthesis.c \
	src/lst_asttree_converter/list_to_asttree/list_to_asttree.c \
	src/lst_asttree_converter/list_to_asttree/converter_split_lst_at_redirection.c \
	src/lst_asttree_converter/list_to_asttree/command_maker.c \
	src/lst_asttree_converter/list_to_asttree/nodetype_flagger.c \
	src/lst_asttree_converter/setup_parenthesis/setup_parenthesis_utils4.c \
	src/lst_asttree_converter/setup_parenthesis/setup_parenthesis_utils.c \
	src/lst_asttree_converter/setup_parenthesis/setup_parenthesis.c \
	src/lst_asttree_converter/setup_parenthesis/potential_parents.c \
	src/lst_asttree_converter/setup_parenthesis/setup_parenthesis_utils2.c \
	src/lst_asttree_converter/setup_parenthesis/setup_parenthesis_utils3.c \
	src/utils/error.c \
	src/utils/ast_tree0.c \
	src/utils/token_utils.c \
	src/utils/main_loop_checks.c \
	src/utils/split_lst_charset.c \
	src/utils/quote_machine.c \
	src/utils/hashtable.c \
	src/utils/split_not_in_quote.c \
	src/utils/path_checker.c \
	src/utils/hashtable3.c \
	src/utils/stack.c \
	src/utils/heredoc_utils2.c \
	src/utils/hashtable2.c \
	src/utils/fds_handler.c \
	src/utils/ast_tree1.c \
	src/utils/ast_tree2.c \
	src/utils/heredoc_utils.c \
	src/utils/param_expander.c \
	src/utils/replace_variable.c \
	src/utils/replace_variable1.c  \
	src/utils/ft_itoa.c \
	src/utils/get_next_line/get_next_line.c \
	src/utils/get_next_line/get_next_line_utils.c \
	src/builtins/b_unset.c \
	src/builtins/b_export0.c \
	src/builtins/b_echo.c \
	src/builtins/b_cd0.c \
	src/builtins/b_export1.c \
	src/builtins/b_pwd.c \
	src/builtins/b_cd3.c \
	src/builtins/b_cd2.c \
	src/builtins/b_env.c \
	src/builtins/b_exit.c \
	src/builtins/b_export2.c \
	src/builtins/b_cd1.c \
	src/environment/environment.c \
	src/exec/exec.c \
	src/exec/exec_cmd2.c \
	src/exec/exec_pipe1.c \
	src/exec/exec_logic_op.c \
	src/exec/exec_cmd0.c \
	src/exec/exec_pipe2.c \
	src/exec/ft_count_param.c \
	src/exec/exec_builtin.c \
	src/exec/exec_pipe0.c \
	src/exec/exec_logic_op1.c \
	src/exec/here_doc0.c \
	src/exec/error_exec.c \
	src/exec/exec_redir.c \
	src/exec/exec_subtree.c \
	src/exec/exec_cmd1.c \
	src/exec/here_doc1.c \
	src/exec/void_node.c \
	src/parsing/parenthesis.c \
	src/parsing/pairs.c \
	src/parsing/tokenization_split.c \
	src/parsing/parsing_error.c \
	src/parsing/parsing_utils.c \
	src/parsing/parsing.c \
	src/parsing/tokenization.c \
	src/parsing/tokenization_utils.c \
	src/expander/expander_utils.c \
	src/expander/expander.c \
	src/expander/wildcard/wildcard.c \
	src/expander/wildcard/wildcard_file_list.c \
	src/expander/wildcard/wilcard_match.c \
	src/expander/word_splitting/word_splitting.c \
	src/expander/quote_remover/quote_remover.c \
	src/expander/var_expander/var_expander_utils.c \
	src/expander/var_expander/var_expander.c \
	src/expander/var_expander/empty_var_cleaner.c \
	src/expander/var_expander/var_expander_replace_var.c \
	src/debug/graph.c \
	src/debug/debug.c

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LIBS = -lreadline -L libft/ -lft
RM = rm -rf
LIBFT = ./libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	make -C libft/

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean lft test
