#include "../../../include/minishell.h"

void	open_file(t_binary *tree)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	while(tmp)
	{
		if ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')) || (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')))
		{
			if (tree->cmd->in)
				close(tree->cmd->in);
			if ( tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
				tree->cmd->in = open(tmp->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if(tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>'))
				tree->cmd->in = open(tmp->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (check_open(tree->cmd->in) == -1)
				break;
		}
		if (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
		{
			tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
			if (check_open(tree->cmd->out) == -1)
				break;
		}
		tmp = tmp->next;
	}
//	tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
}

void	open_file_pipe(t_binary *tree)
{
	t_redirection	*tmp;
	int	pipe_tmp_read;
	int	pipe_tmp_write;
	int	check;

	pipe_tmp_read = tree->cmd->pipe_tmp;
	pipe_tmp_write = tree->cmd->pipe_fd[1];
	check = 0;
	tmp = tree->redir;
	while (tmp)
	{
		if (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
		{
			tree->cmd->pipe_tmp = open(tmp->redir_file, O_RDONLY, 0644);
			if (check_open(tree->cmd->pipe_tmp) == -1)
			{
				tree->cmd->open_ko = -1;
				tree->cmd->pipe_tmp = pipe_tmp_read;
				check++;
				break;
			}
		}
		if ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')) || (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')))
		{
			if (check > 0)
				break;
			if (tree->cmd->pipe_fd[1])
				close(tree->cmd->pipe_fd[1]);
			if ( tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
				tree->cmd->pipe_fd[1] = open(tmp->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if(tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>'))
				tree->cmd->pipe_fd[1] = open(tmp->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (check_open(tree->cmd->pipe_fd[1]) == -1)
			{
				tree->cmd->pipe_fd[1] = pipe_tmp_write;
				check++;
				break;
			}
		}
		tmp = tmp->next;
	}
	if (check > 0)
	{
		perror("open");
	}
//	tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
	return;
}
