#include "../../include/minishell.h"

static void	malloc_redir(t_binary *tree, int i);
static void	malloc_cmd(t_binary *tree);
//static bool	check_redir(char *str);

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
			ft_printf("ok\n");
		}
		i++;
	}
	ft_printf (" size i : [%i], size [j] = [%i] \n", i, j);
	tree->cmd->exec_cmd = ft_malloc2(i - j, "char*");
	malloc_cmd(tree);
	/*i = 0;
	while (tree->cmd->split_cmd[i])
	{
		tree->cmd->exec_cmd[i] = tree->cmd->split_cmd[i];
		i++;
	}*/
	//malloc_cmd(tree, i - j);

	for(int k = 0; tree->cmd->redir_cmd[k]; k++)
		ft_printf("redir_cmd : %s\n", tree->cmd->redir_cmd[k]);
	int p = 0;
	while ( tree->cmd->exec_cmd[p])
	{
		ft_printf("exec: %s\n", tree->cmd->exec_cmd[p]);
		p++;
	}

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



	/*tree->cmd->exec_cmd = NULL;
	while(tree->cmd->split_cmd[i])
	{
		if (check_redir(tree->cmd->split_cmd[i]) == true)
		{
			//malloc_redir(tree, 2, i);
			j = 2;
		}
		i++;
	}
	tree->cmd->exec_cmd = ft_malloc2(i - j, "char *");
	//ft_printf("i : [%i], SIZEE %i\n", i,  i - j);
	//j = i - j;
	i = 0;
	ft_printf("j : putain de j : %i\n", j);
	while ((check_redir(tree->cmd->split_cmd[i]) == false) && tree->cmd->split_cmd[i])
	{

		tree->cmd->exec_cmd[i] = tree->cmd->split_cmd[i];
		//tree->cmd->exec_cmd[i] = ft_malloc(ft_strlen(tree->cmd->split_cmd[i]), "char");
		//tree->cmd->exec_cmd[1] = NULL;
		i++;
	}
	tree->cmd->exec_cmd[i] = NULL;
	int k = 0;
	while (tree->cmd->exec_cmd[k])
	{
		ft_printf("tree->cmd->exec_cmd[%i] : %s\n", k, tree->cmd->exec_cmd[k]);
		k++;
	}
	exit(EXIT_SUCCESS);
	//ft_printf("exec_cmd[%i], j : [%i] : \n", i, j );

	//malloc_cmd(tree, (i - j));

	ft_printf("redi[0] = %s\n", tree->cmd->redir_cmd[0]);
	ft_printf("redi[1] = %s\n", tree->cmd->redir_cmd[1]);
	for (int k = 0; tree->cmd->split_cmd[k] ; k++)
		ft_printf("tree->cmd->split_cmd[%i] : %s\n", k, tree->cmd->split_cmd[k]);
	// recreer une data puis faire appel au split
	return;

}*/

static void	malloc_redir(t_binary *tree, int i)
{
	tree->cmd->redir_cmd = ft_malloc2(2, "char*"); // je malloc de la taille avant la redir
	tree->cmd->redir_cmd[0] = tree->cmd->split_cmd[i];
	tree->cmd->redir_cmd[1] = tree->cmd->split_cmd[i + 1];
	tree->cmd->redir_cmd[2] = NULL;
	return;
}

static void	malloc_cmd(t_binary *tree)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(tree->cmd->split_cmd[i])
	{
		if (is_a_redir(tree->cmd->split_cmd[i]) == true)
		{
			if (tree->cmd->split_cmd[i + 1] != NULL && tree->cmd->split_cmd[i + 2] != NULL)
			{
				i = i + 2;
			}
			//else
			//	break ;
		}
		tree->cmd->exec_cmd[j] = tree->cmd->split_cmd[i];
		i++;
		j++;
	}
	tree->cmd->exec_cmd[j] = NULL;
	return;
}
/*
static bool	check_redir(char *str) // check si une redir ou non
{
	int	i;
	int	count_1;
	int	count_2;

	i = 0;
	count_1 = 0;
	count_2 = 0;
	while(i < 2)
	{
		if (ft_strcmp(str[i] == '>')
			count_1++;
		else if (str[i] == '<')
			count_2++;
		i++;
	}
	if (count_1 == 1 && || count_1 == 2 || count_2 == 1 || count_2 == 2)
		return (true);
	else
		return (false);
}


void	mini_pipe(t_binary *tree, t_minishell *mini)
{


}*/
