#include "../../../include/minishell.h"

int	count_redir_right(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	//tree->redir->redir_right = false;
	//exit(EXIT_SUCCESS);
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>')
		{
			count++;
			//tree->redir->redir_right = true;
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
	//tree->redir->redir_double_right = false;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')
		{
			count++;
			//tree->redir->redir_double_right = true;
		}
		tmp = tmp->next;
	}
	return (count);
}

int	count_redir_left(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	//tree->redir->redir_left = false;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<')
		{
			count++;
			//tree->redir->redir_left = true;
		}
		tmp = tmp->next;
	}
	return (count);
}