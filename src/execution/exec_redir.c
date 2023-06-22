#include "../../include/minishell.h"

void exec_cmd_redir(t_binary *tree, t_minishell *mini)
{
	int	i;
	int	j;
	t_redirection	*tmp;
	(void)mini;

	i = 0;
	j = 0;


	tmp = tree->redir;	
	if ((tmp))
	{
		ft_printf("test");
		while((tmp))
		{
			ft_printf("redir_cmd : %s\n", tmp->redir_cmd);
			ft_printf("redir_file: %s\n", tmp->redir_file);
			tmp = tmp->next;
		}
	}
	for (int p = 0; tree->cmd->exec_cmd[p]; p++)
		ft_printf("exec_cmd : %s\n", tree->cmd->exec_cmd[p]);

}
/*void	exec_cmd_redir(t_minishell *mini, t_binary *tree)
{
	while (tree)
}*/

