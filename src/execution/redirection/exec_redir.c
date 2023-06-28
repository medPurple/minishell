#include "../../../include/minishell.h"

void exec_cmd_redir(t_binary *tree, t_minishell *mini)
{
	(void)mini;

	if (count_redir_right(tree) >= 1 || count_redir_right_double(tree) >= 1)
	{
		if (dup2(tree->cmd->in, STDOUT_FILENO) == -1)
				perror("dup2");
		close(tree->cmd->in);
	}
	if (count_redir_left(tree) >= 1)
	{
		if (dup2(tree->cmd->out, STDIN_FILENO) == -1)
				perror("dup2");
		close(tree->cmd->out);
	}
	return;
}








