#include "../../include/minishell.h"
static void parse_data(t_binary *tree, t_env *env);
static void create_root(t_binary *tree, t_env *env);
static int find_next_split(t_binary *tree, t_env *env);
static bool string_analyse(char *str, t_env *env);
static int split_pos(char *str, t_env *env, int j , int i);
static void ignore_parentheses(t_binary *tree);
static int end_of_quotes(char *str, int i);
static bool is_a_meta(char c);
static int pass_quotes(char *str, int i);

static t_binary *new_branche(t_binary *tree, char *str)
{
	tree = malloc(sizeof(t_binary));
	//tree->data = NULL;
	//tree->data = ft_malloc(ft_strlen(str), "char");
	tree->data = str;
	tree->end = 0;
	tree->prev = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->command = NULL;
	tree->rest = NULL;
	return (tree);
}

void parse_test(t_minishell *mini, char *str)
{
	mini->tree = new_branche(mini->tree, str);
	while (mini->tree->end != 1)
		parse_data(mini->tree, mini->env);
}

static void parse_data(t_binary *tree, t_env *env)
{
	if (tree->left == NULL)
		create_root(tree, env);
	if (tree->command == NULL) {
			tree->end = 1;
			return;
	}
	tree->left = new_branche(tree->left, tree->command);
	tree->right = new_branche(tree->right, tree->rest);
	ft_printf ("\n\ntree left = %s |||| ", tree->left->data);
	ft_printf ("tree right = %s \n", tree->right->data);
	tree->right->prev = tree;
	tree->left->prev = tree;
	if (tree->right != NULL && tree->right->end != 1)
		parse_data(tree->right, env);
	if (tree->right->end == 1)
		tree->end = 1;
}

static void split_char(t_binary *tree)
{
	int i;

	i = 0;
	while (is_a_meta(tree->data[i]) == true)
		i++;
	tree->command = ft_limited_strdup(tree->data,0,i);
	tree->rest = ft_limited_strdup(tree->data,i+1, ft_strlen(tree->data));
}

static void create_root(t_binary *tree, t_env *env)
{
	int split;

	if (tree->data[0] == '(')
		ignore_parentheses(tree);
	else if (is_a_meta(tree->data[0]) == true)
		split_char(tree);
	else{
		split = find_next_split(tree, env);
		if (split == -1)
			return;
		else
		{
			tree->command = ft_limited_strdup(tree->data,0,split);
			tree->rest = ft_limited_strdup(tree->data,split + 1, ft_strlen(tree->data));
		}
		return;
	}
}

static int find_next_split(t_binary *tree, t_env *env)
{
	int i = 0;
	int j = 0;
	char *str;

	while(tree->data[i] != '\0')
	{

		while(tree->data[i] != '\0' && tree->data[i] != ' ' && tree->data[i] != '\t')
		{
			if (tree->data[i] == '\'' || tree->data[i] == '\"')
				i = end_of_quotes(tree->data, i);
			else
				i++;
		}
		str = ft_limited_strdup(tree->data, j, i - 1);
		if (string_analyse(str,env) != true)
		{
			free(str);
			while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
				i++;
			j = i;
		} else
		{
			if (j == 0 && (is_a_fonction(str, env) || is_a_buildin(str))) {
				free(str);
				while ((tree->data[i] == ' ' || tree->data[i] == '\t') && tree->data[i] != '\0')
					i++;
				j = i;
			}
			else
				return(split_pos(tree->data, env, j, i - 1));
		}

		if (tree->data[i] == '\0')
			return (-1);
	}
	return (-1);
}

static bool string_analyse(char *str, t_env *env)
{
	int i = 0;

	if (is_a_fonction(str, env) || is_a_buildin(str))
		return(true);
	else
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = end_of_quotes(str, i);
			else{
				if((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (true);
				i++;
			}
		}
		return(false);
	}
}

static int split_pos(char *str, t_env *env, int j, int i)
{
	char *str_a = ft_limited_strdup(str, j, i);
	if (is_a_fonction(str_a, env) || is_a_buildin(str_a))
	{
		return(j - 1);
	}
	else
	{
		i = j;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				i = end_of_quotes(str, i);
				return (i - 1);
			}
			else {
				if ((str[i]) == '(' || str[i] == '&' || str[i] == '|' || str[i] == '<' || str[i] == '>')
					return (i - 1);
				i++;
			}
		}
	}
	return (-1);

}

static void ignore_parentheses(t_binary *tree)
{
	int i = 1;
	int para_count = 1;

	while (para_count != 0)
	{
		if (tree->data[i] == '\0')
			break;
		if (tree->data[i] == ')')
			para_count--;
		else if (tree->data[i] == '(')
			para_count++;
		i++;
	}
	if (i != (int)ft_strlen(tree->data))
	{
		tree->command = ft_limited_strdup(tree->data, 0, i);
		tree->rest = ft_limited_strdup(tree->data, i+1, ft_strlen(tree->data));
	} else
		return;
}

static int end_of_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	i++;
	while (is_a_meta(str[i]) != true)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	return (i);

}

static bool is_a_meta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	else
		return (false);
}

static int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	while(str[i] != c)
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		i++;
	}
	return (i);
}
//ok tant qu'on a pas croisee un metacar on avance.