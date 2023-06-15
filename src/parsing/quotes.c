#include "../../include/minishell.h"

int pass_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while(str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

int end_of_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	while ((str[i] != '&' && str[i+1] != '&') && (str[i] != '|' && str[i+1] != '|') && str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
		else
			i++;
	}
	return (i);
}

int	find_next_quotes (char *str, int pos)
{
	pos++;
	while (str[pos] != '\0')
	{
		if (str[pos] == '\"')
			return(pos);
		pos++;
	}
	return (-1);
}