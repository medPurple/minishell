#include "../../include/minishell.h"

static void	malloc_redir(t_binary *tree, int i);
static void	malloc_cmd(t_binary *tree, int size);
static void malloc_cmd_redir(t_binary *tree);
static bool is_a_redir(char *cmd);

void split_exec(t_binary *tree, t_minishell *mini)
{
	(void)mini;
	int	i;
	int	j;

	i = 0;
	j = 0;
	malloc_cmd_redir(tree);

}
static void malloc_cmd_redir(t_binary *tree)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tree->cmd->split_cmd[i])
	{
		if(is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			j = 2;
			malloc_redir(tree, i);
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 2;
		}
		i++;
	}
	malloc_cmd(tree, i - j);

	if (tree->cmd->redir_cmd)
	{
		for(int k = 0; tree->cmd->redir_cmd[k]; k++)
			ft_printf("redir_cmd : %s\n", tree->cmd->redir_cmd[k]);
	}
	for(int p = 0; tree->cmd->exec_cmd[p]; p++)
			ft_printf("exec_cmd : %s\n", tree->cmd->exec_cmd[p]);

}

static bool is_a_redir(char *cmd)
{
	int	pos;

	int	count_left;
	int	count_right;
	int	count_pipe;

	count_left = 0;
	count_right = 0;
	count_pipe = 0;

	pos = 0;
	while (cmd[pos])
	{
		if (cmd[pos] == '>')
			count_right++;
		else if (cmd[pos] == '<')
			count_left++;
		else if (cmd[pos] == '|' )
			count_pipe++;
		pos++;
	}
	if ((count_right == 1 || count_right == 2) && (count_left == 0) && (count_pipe == 0))
		return (true);
	else if ((count_left == 1 || count_left == 2) && (count_right == 0) && (count_pipe == 0))
		return (true);
	else if ((count_pipe == 1) && (count_left == 0) && (count_right == 0))
		return (true);
	else
		return (false);
}

static void	malloc_redir(t_binary *tree, int i)
{
	tree->cmd->redir_cmd = ft_malloc2(2, "char*");
	tree->cmd->redir_cmd[0] = tree->cmd->split_cmd[i];
	tree->cmd->redir_cmd[1] = tree->cmd->split_cmd[i + 1];
	tree->cmd->redir_cmd[2] = NULL;
	return;
}

static void	malloc_cmd(t_binary *tree, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tree->cmd->exec_cmd = ft_malloc2(size, "char*");
	while(tree->cmd->split_cmd[i])
	{
		if (is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 2;
			else
				break ;
		}
		tree->cmd->exec_cmd[j] = tree->cmd->split_cmd[i];
		i++;
		j++;
	}
	tree->cmd->exec_cmd[j] = NULL;
	return;
}
