#include "../../include/minishell.h"
static int word_nb(char *str);
static int after_quotes(char *str, int i);


char **mini_split(char *str) {
	int i;
	char **cmd;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	cmd = ft_malloc2(word_nb(str), "char*");
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		j = i;
		while ((str[i] != ' ' || str[i] != '\t') && str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = after_quotes(str, i);
			i++;
		}
		cmd[k] = ft_limited_strdup(str, j, i);
		k++;
		}
	return(cmd);
}

static int after_quotes(char *str, int i)
{
	char c;

	c = str[i];
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
static int word_nb(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		{
			count++;
			while ((str[i] != ' ' || str[i] != '\t') && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = after_quotes(str, i);
				i++;
			}
		}

	}
	return (count);
}