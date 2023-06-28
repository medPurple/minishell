#include "../../include/minishell.h"


bool is_a_redir(char *cmd)
{
	int	pos;
	int	count_left;
	int	count_right;
	int	count_pipe;

	count_left = 0;
	count_right = 0;
	count_pipe = 0;
	pos = 0;
	while (cmd[pos])
	{
		if (cmd[pos] == '>')
			count_right++;
		else if (cmd[pos] == '<')
			count_left++;
		else if (cmd[pos] == '|' )
			count_pipe++;
		pos++;
	}
	if ((count_right == 1) && (count_left == 0) && ((count_pipe == 0) || count_pipe == 1))
		return (true);
	else if ((count_right == 2) && (count_left == 0) && (count_pipe == 0))
		return (true);
	else if ((count_left == 1 || count_left == 2) && (count_right == 0) && (count_pipe == 0))
		return (true);
	else
		return (false);
}

bool is_a_pipe(char *cmd)
{
	int	count_pipe;
	int	pos;


	count_pipe = 0;
	pos = 0;
	while (cmd[pos])
	{
		if (cmd[pos] == '|' )
			count_pipe++;
		pos++;
	}
	if (count_pipe == 1)
		return (true);
	else
		return (false);
}
