
#include "../../include/minishell.h"

static int	nb_redir(t_binary *tree, int count_right, int count_left);

int    analyze_error(t_binary *tree)
{
	int	count;
	if (tree->redir)
	{
		count = nb_redir(tree, 0, 0);
		if ((tree->redir->redir_cmd[0] == '<') && tree->redir->redir_cmd[1] == '|')
			return (mini_error_one(4), -1);
		else if ((tree->redir->redir_cmd[0] == '>' && count > 3))
			return (mini_error_one(3), -1);
		else if (tree->redir->redir_cmd[0] == '>' && count == 3)
			return (mini_error_one(2), -1);
		else if ((tree->redir->redir_cmd[0] == '>' || tree->redir->redir_cmd[0] == '<') && count < 3 && ft_strlen(tree->redir->redir_file) == 0)
			return (mini_error_one(1), -1);
		else if ((tree->redir->redir_cmd[0] == '<' && count > 3))
			return (mini_error_one(7), -1);
		else if (tree->redir->redir_cmd[0] == '<' && count == 3)
			return (mini_error_one(6), -1);
		else
			return (0);
	}
	return (0);
}

static int	nb_redir(t_binary *tree, int count_right, int count_left)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(tree->cmd->split_cmd[i])
	{
		j = 0;
		while (tree->cmd->split_cmd[i][j])
		{
			if (tree->cmd->split_cmd[i][j] == '>')
				count_right++;
			if (tree->cmd->split_cmd[i][j] == '<')
				count_left++;
			j++;
		}
		i++;
	}
	if (tree->redir->redir_cmd[0] == '>')
		return (count_right);
	else
		return (count_left);
}
