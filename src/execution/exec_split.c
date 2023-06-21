#include "../../include/minishell.h"

void split_exec(t_binary *tree, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	malloc_cmd_redir(mini, tree);
	//exec_cmd_redir(mini, tree);
	if ((tree->redir))
	{
		while((tree->redir))
		{
			ft_printf("redir_cmd : %s\n", tree->redir->redir_cmd);
			ft_printf("redir_file: %s\n", tree->redir->redir_file);
			tree->redir = tree->redir->next;
		}
	}
	for (int p = 0; tree->cmd->exec_cmd[p]; p++)
		ft_printf("exec_cmd : %s\n", tree->cmd->exec_cmd[p]);

}

