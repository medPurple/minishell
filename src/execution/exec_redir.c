#include "../../include/minishell.h"

static char	**malloc_redir(t_binary *tree, int i);
static char	**malloc_cmd(t_binary *tree, int i, int j);
static bool	check_redir(char *str);

void split_exec(t_binary *tree, t_minishell *mini) // split en plusieurs morceau en fonction de si redir ou non
{
	(void)mini;
	int	i;
	int	j;

	i = 0;
	j = 0;

	while(tree->cmd->split_cmd[i])
	{
		if (check_redir(tree->cmd->split_cmd[i]) == true)
		{
			tree->cmd->redir_cmd = malloc_redir(tree, );
			j = 2;
		}
		i++;
	}
	tree->cmd->exec_cmd = malloc_cmd(tree, i, j);

	for(int cmd = 0 ; tree->cmd->exec_cmd[cmd] ; cmd++)
		ft_printf("exec_cmd = %s\n", tree->cmd->exec_cmd[cmd]);
	for(int redir = 0 ;tree->cmd->redir_cmd[redir] ; redir++)
		ft_printf("redir_cmd = %s\n", tree->cmd->redir_cmd[redir]);

	// recreer une data puis faire appel au split


}

static char	**malloc_redir(t_binary *tree, int i)
{
	char	**redir;

	redir = ft_malloc2(i, "char*"); // je malloc de la taille avant la redir
	while (i > 0)
	{
		redir[i] = tree->cmd->split_cmd[i];
		i--;
	}
	return(redir);
}

static char	**malloc_cmd(t_binary *tree, int i, int j)
{
	char	**cmd;

	cmd = ft_malloc2((i - j), "char *");
	while(tree->cmd->split_cmd[i])
	{
		if (check_redir(tree->cmd->split_cmd[i]) == true)
			i = i - 2;
		cmd[i] = tree->cmd->split_cmd[i];
		i--;
	}
	return (cmd);
}

static bool	check_redir(char *str) // check si une redir ou non
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			count++;
		i++;
	}
	if (count == 1 || count == 2)
		return (true);
	else
		return (false);
}


/*void	mini_pipe(t_binary *tree, t_minishell *mini)
{


}*/
