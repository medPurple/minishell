#include "../../../include/minishell.h"

void exec_cmd_redir(t_binary *tree, t_minishell *mini)
{
	t_redirection	*tmp;
	(void)mini;

	tmp = tree->redir;
	if (count_redir_right(tree) >= 1 || count_redir_right_double(tree) >= 1)
	{
		if (dup2(tree->cmd->in, STDOUT_FILENO) == -1)
				perror("dup2");
		close(tree->cmd->in);
	}
	else if (count_redir_left(tree) >= 1)
	{
		if (dup2(tree->cmd->out, STDIN_FILENO) == -1)
				perror("dup2");
		close(tree->cmd->out);
	}
	return;
}

void	open_file_right(t_binary *tree)
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
			if (check_open(tree->cmd->out) == -1)
					break;
	}
	tmp = tree->redir;
//	tree->cmd->out = open(tmp->redir_file, O_RDONLY, 0644);
	}
}

int	count_redir_right(t_binary *tree)
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

int	count_redir_right_double(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')
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




