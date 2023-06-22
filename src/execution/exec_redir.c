#include "../../include/minishell.h"

void exec_cmd_redir(t_binary *tree, t_minishell *mini)
{
	t_redirection	*tmp;
	(void)mini;

	tmp = tree->redir;
	if (count_redir(tree) >= 1)
	{
		if (dup2(tree->cmd->in, STDOUT_FILENO) == -1)
				perror("dup2");
		close(tree->cmd->in);
	}
	return ;
}

void	open_file(t_binary *tree)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	while (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
	{
		if (tree->cmd->in)
			close(tree->cmd->in);
		tree->cmd->in = open(&tmp->redir_file[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	    if (tree->cmd->in == -1)
		    perror("open");
		tmp = tmp->next;
	}
}

int	count_redir(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}



	/*}
		while((tmp))
		{
			ft_printf("redir_cmd : %s\n", tmp->redir_cmd);
			ft_printf("redir_file: %s\n", tmp->redir_file);
			tmp = tmp->next;
		}
	}
	for (int p = 0; tree->cmd->exec_cmd[p]; p++)
		ft_printf("exec_cmd : %s\n", tree->cmd->exec_cmd[p]);*/




