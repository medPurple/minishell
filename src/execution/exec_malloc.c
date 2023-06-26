#include "../../include/minishell.h"

static void	malloc_redir(t_binary *tree, int i);
static void	malloc_cmd(t_binary *tree, int size, int i);

/*ajouter char *exec_cmd dans la structre redirection afin de pouvoir chainer chaque cmd des
que je croise un pipe autrement dit dans chaque maillon il y aura : 1 pipe et 1 cmd
tant que le maillon suivant contient 1 pipe je continuem sinon j'arrete et je regarde s'il y a une redirection
ou autre */

int malloc_cmd_redir(t_minishell *mini, t_binary *tree, int i)
{
	int	j;
	int	save_pos;

	j = i;
	save_pos = i;
	(void)mini;
	while (tree->cmd->split_cmd[i])
	{
		if(is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			j = 2;
			malloc_redir(tree, i);
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 1;
		}
		else if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
			break;
		i++;
	}
	malloc_cmd(tree, i - j, save_pos);
	return (i);
}

static void		malloc_redir(t_binary *tree, int i)
{
	t_redirection	*tmp;

	tmp = ft_new_redirection(ft_strdup(tree->cmd->split_cmd[i]), ft_strdup(tree->cmd->split_cmd[i + 1]));
	ft_add_back_lst_redirection(&tree->redir, tmp);
	return;
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
		else if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
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
