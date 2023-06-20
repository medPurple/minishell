#include "../../include/minishell.h"

static void	malloc_redir(t_redirection **redir, t_binary *tree, int i);
static void	malloc_cmd(t_binary *tree, int size);


void malloc_cmd_redir(t_minishell *mini, t_binary *tree)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	t_redirection *redir = NULL;
	(void)mini;
	while (tree->cmd->split_cmd[i])
	{
		if(is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			j = 2;
			malloc_redir(&redir, tree, i);// tre[i] && tree[i+1]
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i = i + 2;
		}
		else if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
		{
			return;
			//ft_printf("coucou\n");
			//exit(EXIT_SUCCESS);
		}
		i++;
	}
	malloc_cmd(tree, i - j);
 // ci dessous a supprimer
	if (redir->redir_cmd)
	{
		while(redir->next)
		{
			ft_printf("redir_cmd : %s\n", redir->redir_cmd);
			redir = redir->next;
		}
	}
	for(int p = 0; tree->cmd->exec_cmd[p]; p++)
			ft_printf("exec_cmd : %s\n", tree->cmd->exec_cmd[p]);

}

static void		malloc_redir(t_redirection **redir, t_binary *tree, int i)
{
	t_redirection	*tmp;
	t_redirection	*wait;

	tmp = ft_new_redirection(ft_strdup(tree->cmd->split_cmd[i]), ft_strdup(tree->cmd->split_cmd[i + 1]));
	ft_add_back_lst_redirection(redir, tmp);
	wait = (*redir);
	while((*redir))
		{
			ft_printf("redir_cmd : %s\n", (*redir)->redir_cmd);
			ft_printf("redir_cmd : %s\n", (*redir)->redir_file);
			(*redir) = (*redir)->next;
		}
		(*redir) = wait;
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
		else if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
		{
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
				i++;
			else
				break;
		}
		tree->cmd->exec_cmd[j] = tree->cmd->split_cmd[i];
		i++;
		j++;
	}
	tree->cmd->exec_cmd[j] = NULL;
	return;
}
