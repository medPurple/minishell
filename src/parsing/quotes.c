#include "../../include/minishell.h"

int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	while(str[i] != c && str[i] != '\0')
	{
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
	}
	i++;
	while (is_a_meta(str[i]) != true && str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	return (i);

}
