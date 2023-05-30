#include "../../include/minishell.h"

void replace_parentheses(t_binary *tree, t_env *env)
{
	int	i;

	i = ft_strlen(tree->data) - 1;
	while(tree->data[i] == ' ' || tree->data[i] == '\t')
		i--;
	tree->parentheses = true;
	tree->data = ft_limited_strdup(tree->data, 1, i - 1);
	while (tree->end != 1)
		parse_data(tree, env);
}
void ignore_parentheses(t_binary *tree)
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
