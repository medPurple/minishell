#include "../../../include/minishell.h"

int	count_redir_right(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;
	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '>'&& tmp->redir_cmd[1] != '>')
			count++;

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
		if (tmp->redir_cmd[0] == '>'&& tmp->redir_cmd[1] == '>')
			count++;
		tmp = tmp->next;
	}
	return (count);
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
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	last_pipe_redir(t_binary *tree, int i)
{
	while(tree->cmd->split_cmd[i])
	{
		if (tree->cmd->split_cmd[i][0] == '>')
			return(1);
		i++;
	}
	return(0);
}
