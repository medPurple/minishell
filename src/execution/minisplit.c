#include "../../include/minishell.h"
static int word_nb(char *str);
static int after_quotes(char *str, int i);
static	int is_a_redir_or_pipe (char *str, int start, int end);


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
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && is_a_redir_or_pipe(str, i, i + 4) > 0)
		{
			j = i;
			i = i + is_a_redir_or_pipe(str, i, i + 4);
			cmd[k++] = ft_limited_strdup(str, j, i - 1);
		}
		else
		{
			j = i;
			while ((str[i] != ' ' && str[i] != '\t') && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = after_quotes(str, i);
				if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && (is_a_redir_or_pipe(str, i, i + 4) > 0))
				{
					if (str[i - 1] != ' ' && str[i - 1] != '\t')
						break;
				}
				i++;
			}
			if (i == j)
				break;
			cmd[k++] = ft_limited_strdup(str, j, i - 1);
		}

	}
	cmd[k] = NULL;
	return(removes_quotes(cmd));
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
			while ((str[i] != ' ' && str[i] != '\t') && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = after_quotes(str, i);
				if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && (is_a_redir_or_pipe(str, i, i+4) > 0))
				{
					count++;
					i = i + is_a_redir_or_pipe(str, i, i + 4) + 1;
					break;
				}
				i++;
			}
		}
	}
	return (count);
}

static	int is_a_redir_or_pipe (char *str, int start, int end)
{
	int	count_left;
	int	count_right;
	int	count_pipe;


	count_left = 0;
	count_right = 0;
	count_pipe = 0;

	while (start < end)
	{
		if (str[start] == '>')
			count_right++;
		else if (str[start] == '<')
			count_left++;
		else if (str[start] == '|' )
			count_pipe++;
		start++;
	}
	if ((count_right == 1) && (count_left == 0) && (count_pipe == 0))
		return (1);
	else if ((count_right == 2) && (count_left == 0) && (count_pipe == 0))
		return (2);
	else if ((count_left == 1) && (count_right == 0) && (count_pipe == 0))
		return (1);
	else if ((count_left == 2) && (count_right == 0) && (count_pipe == 0))
		return (2);
	else if ((count_left ==  0 || count_left == 0) && (count_right == 0) && (count_pipe == 1))
		return (1);
	else
		return (-1);

}