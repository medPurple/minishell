#include "../../include/minishell.h"

void	execution_choice(t_binary *tree, t_minishell *mini, int i)
{
	char	**cmd;

	cmd = NULL;
	if (is_here_doc(tree) >= 1)
        mini_here_doc(tree->redir->redir_file, tree);
	else if (is_a_buildin(tree->cmd->exec_cmd[0]) == 1)
        exec_buildin(tree, mini);
	if ((count_redir_right(tree) >= 1) || (count_redir_right_double(tree) >= 1) || (count_redir_left(tree) >= 1))
    {
		open_file_right(tree);
		if (check_open(tree->cmd->out) == -1)
					return;
		exec_send(tree, mini);

	}
	/*else if (count_redir_left(tree) >= 1)
    {
		open_file_left(tree);
		exec_send(tree, mini);

	}*/
	else if (tree->cmd->split_cmd[i] != NULL && is_a_pipe(tree->cmd->split_cmd[i]) == true)
	{
		exec_pipe(tree, mini);
	}
	else
		exec_send(tree, mini);
	//ft_free_tab(tree->cmd->exec_cmd);
	return;
}
