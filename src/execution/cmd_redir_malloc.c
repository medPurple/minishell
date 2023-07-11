#include "../../include/minishell.h"

static int	malloc_redir(t_binary *tree, int i);
static void	malloc_cmd(t_binary *tree, int size, int i);

int cmd_redir_malloc(t_binary *tree, int i)
{
	int	j;
	int	save_pos;

	j = i;
	save_pos = i;
	while (tree->cmd->split_cmd[i])
	{
		if(is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			j = 2;
			tree->redir->ok = malloc_redir(tree, i);
			tree->cmd->is_a_redir = 1;
			if (tree->redir->ok < 0)
			{
				tree->cmd->open_ko = tree->redir->ok;
				break;
			}
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 1;
		}
		if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
			break;
		i++;
	}
	if (i - j < 0)
		return(-1);
	malloc_cmd(tree, i - j, save_pos);
	return (i);
}

static int		malloc_redir(t_binary *tree, int i)
{
	t_redirection	*tmp;
	t_redirection	*tmp2;

	tmp = ft_new_redirection(ft_strdup(tree->cmd->split_cmd[i]), ft_strdup(tree->cmd->split_cmd[i + 1]));
	ft_add_back_lst_redirection(&tree->redir, tmp);
	tmp2 = tree->redir;
	while (tmp2)
	{
		if (redir_is_valid(tmp2->redir_file) < 0)
			return (redir_is_valid(tmp2->redir_file));
		tmp2 = tmp2->next;
	}
	return(0);
}

static void	malloc_cmd(t_binary *tree, int size, int i)
{
	int	j;

	j = 0;
	tree->cmd->exec_cmd = ft_malloc2(size, "char*");
	while(tree->cmd->split_cmd[i])
	{
		if (is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 2;
			else
				break;
		}
		if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
				break;
		tree->cmd->exec_cmd[j] = tree->cmd->split_cmd[i];
		if (is_a_redir(tree->cmd->split_cmd[i]) == false)
		{
			i++;
			j++;
		}
	}
	tree->cmd->exec_cmd[j] = NULL;
	return;
}


int redir_is_valid(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return(-1);
	if (str[0] == '<' && str[1] != '<')
		return (-2);
	if (str[0] == '>' && str[1] == '>')
		return (-3);
	if (str[0] == '>' && str[1] != '>')
		return (-4);
	if (str[0] == '|')
		return(-5);
	if (str[0] == '\0')
		return(-6);
	return (0);
}
