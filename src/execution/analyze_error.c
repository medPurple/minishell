
#include "../../include/minishell.h"

static int	nb_redir(t_binary *tree, int count_right, int count_left);

void    analyze_error(t_binary *tree)
{
	int	count;

	if (tree->redir)
	{
		count = nb_redir(tree, 0, 0);
		if ((tree->cmd->split_cmd[0][0] == '>' && count > 3))
			mini_error_one(3);
		else if (tree->cmd->split_cmd[0][0] == '>' && count == 3)
			mini_error_one(2);
		else if ((tree->cmd->split_cmd[0][0] == '>' || tree->cmd->split_cmd[0][0] == '<') && count < 3)
			mini_error_one(1);
		else if ((tree->cmd->split_cmd[0][0] == '<' && count > 3))
			mini_error_one(7);
		else if (tree->cmd->split_cmd[0][0] == '<' && count == 3)
			mini_error_one(6);

	}
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
	if (tree->cmd->split_cmd[0][0] == '>')
		return (count_right);
	else
		return (count_left);
}
