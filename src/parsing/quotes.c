#include "../../include/minishell.h"

int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while(str[i] != c && str[i] != '\0')
	{
		//if (str[i+1] == '\0')
		//	return (-1);
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		i++;
	}
	return (i);
}

int end_of_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] != c && str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
		//if (i == -1)
		//	return (-1);
	}
	i++;
	while (is_a_meta(str[i]) != true && str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
		//if (i == -1)
		//	return (-1);
	}
	return (i);
}

/*void	expand_quotes(t_binary *tree, t_env *env)
{
	int	i;

	i = 0;
	while(tree->data[i] == ' ' || tree->data[i] == '\t' ||tree->data != '\0')
		i++;
	if (tree->data[i] == '\'' || tree->data[i] == '\"')
	{
		is_executable(tree->data, i, env);
	}

}

void is_executable(char *str, int pos, t_env *env)
{
	while()
	//is_a_fonction
}*/
