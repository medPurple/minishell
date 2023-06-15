#include "../../include/minishell.h"

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
	while ((is_a_meta(tree->data, i) != true) && tree->data[i])
		i++;
	if (i != (int)ft_strlen(tree->data))
	{
		tree->command = ft_limited_strdup(tree->data, 0, i - 1);
		tree->rest = ft_limited_strdup(tree->data, i, ft_strlen(tree->data));
	} else
		return;
}

int end_of_parentheses(char *str, int position)
{
	int i = position + 1;
	int para_count = 1;

	while (para_count != 0 && str[i])
	{
		if (str[i] == '\0')
			break;
		if (str[i] == ')')
			para_count--;
		else if (str[i] == '(')
			para_count++;
		i++;
	}
	return (i);
}