#include "../../include/minishell.h"

int parsing(t_minishell *mini, char *str)
{
	mini->tree = new_branche(mini->tree, str);
	while (mini->tree->end != 1)
		parse_data(mini->tree, mini->env);
	if (verif_parentheses(mini->tree) == -1)
	{
		return (-1);
	}
	create_cmd_in_tree(mini->tree);
	return (0);
}

void parse_data(t_binary *tree, t_env *env)
{
	if (tree->left == NULL)
		create_root(tree, env);
	if (tree->command == NULL) {
		if (tree->data[0] != '(')
			expand(tree, env);
		tree->end = 1;
		return;
	}
	tree->left = new_branche(tree->left, tree->command);
	tree->right = new_branche(tree->right, tree->rest);
	//ft_printf("Left - %s\n",tree->left->data);
	//ft_printf("Right - %s\n",tree->right->data);
	if (tree->left->data[0] == '(')
		tree->left->parentheses = true;
	if (tree->left->data[0] != '(')
		expand(tree->left, env);
	tree->right->prev = tree;
	tree->left->prev = tree;
	if (tree->right != NULL && tree->right->end != 1)
		parse_data(tree->right, env);
	if (tree->right->end == 1)
		tree->end = 1;
}

void create_root(t_binary *tree, t_env *env)
{
	int split;
	int i;

	i = 0;	
	while (tree->data && tree->data[i] == ' ')
		i++;
	if (i != 0)
		tree->data = ft_limited_strdup(tree->data, i, ft_strlen(tree->data));	
	if (tree->data[0] == '(')
		ignore_parentheses(tree);
	else if (is_a_meta(tree->data, 0) == true)
		split_char(tree);
	else{
		if (has_nothing(tree->data) == true)
			return;
		split = find_next_split(tree, env);
		if (split == -1)
			return;
		else
		{
			tree->command = ft_limited_strdup(tree->data,i,split);
			tree->rest = ft_limited_strdup(tree->data,split + 1, ft_strlen(tree->data));
		}
		return;
	}
}

t_binary *new_branche(t_binary *tree, char *str)
{
	tree = malloc(sizeof(t_binary));
	tree->parentheses = false;
	tree->data = str;
	tree->end = 0;
	tree->prev = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->command = NULL;
	tree->rest = NULL;
	tree->redir = NULL;
	return (tree);
}

void create_cmd_in_tree(t_binary *tree)
{
	if (tree->right) {
		create_cmd_in_tree(tree->left);
		create_cmd_in_tree(tree->right);
	} else
		create_cmd(tree);
}

//ok tant qu'on a pas croisee un metacar on avance.
