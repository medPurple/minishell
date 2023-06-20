#include "../../include/minishell.h"

void split_exec(t_binary *tree, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	malloc_cmd_redir(mini, tree);

}
