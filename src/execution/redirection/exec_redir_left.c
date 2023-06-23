#include "../../../include/minishell.h"

void	open_file_left(t_binary *tree)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	while (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
	{
		tree->cmd->out = open(&tmp->redir_file[0], O_RDONLY, 0644);
	    if (tree->cmd->out == -1)
		    perror("open");
		close(tree->cmd->out);
		tmp = tmp->next;
	}
	tmp = tree->redir;
	tree->cmd->out = open(&tmp->redir_file[0], O_RDONLY, 0644);
}

int	count_redir_left(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

