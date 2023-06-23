#include "../../include/minishell.h"

int	count_pipe(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '|')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

