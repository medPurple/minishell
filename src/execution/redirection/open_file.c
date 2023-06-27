#include "../../../include/minishell.h"



void	open_file(t_binary *tree)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	if ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')) || (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')) || (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<')))
	{
		while(tmp)
		{
			while ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')) || (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')))
			{
				if (tree->cmd->in)
					close(tree->cmd->in);
				if ( tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
					tree->cmd->in = open(tmp->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if(tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>'))
					tree->cmd->in = open(tmp->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (check_open(tree->cmd->in) == -1)
					break;
				tmp = tmp->next;
			}
			while (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
			{
				tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
				if (check_open(tree->cmd->out) == -1)
					break;
				tmp = tmp->next;
			}
			if (check_open(tree->cmd->out) == -1 || check_open(tree->cmd->in) == -1)
					break;
	}
	tmp = tree->redir;
//	tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
	}
}

