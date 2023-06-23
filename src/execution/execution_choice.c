#include "../../include/minishell.h"

void	execution_choice(t_binary *tree, t_minishell *mini)
{
	int	i;
	char	**cmd;

	cmd = NULL;
	i = 0;
	if (is_here_doc(tree) >= 1)
        mini_here_doc(tree->redir->redir_file, tree);
	else if (is_a_buildin(tree->cmd->exec_cmd[0]) == 1)
        exec_buildin(tree, mini);
	if ((count_redir_right(tree) >= 1) || (count_redir_right_double(tree) >= 1))
    {
		open_file_right(tree);
		exec_send(tree, mini);

	}
	else if (count_redir_left(tree) >= 1)
    {
		open_file_left(tree);
		exec_send(tree, mini);

	}
	else if (count_pipe(tree) >= 1)
	{
		while(tree->cmd->exec_cmd[i] != NULL)
		{
			cmd[i] == tree->cmd->exec_cmd[i]
				i++;
			exec_pipe(tree, mini, cmd);
			i++;
		}
	}
	else
    	exec_send(tree, mini);
}

void    exec_pipe(t_binary *tree, t_minishell *mini)
{
    char	buf[6];
	int	ret;
    t_redirection	*tmp;

    tmp = tree->redir;
	tree->cmd->exec = 1;
    if (pipe(tree->cmd->fd) == -1)
        perror("pipe");
    tree->cmd->fork = fork();
    if (tree->cmd->fork == -1)
        perror("fork");
	else if(tree->cmd->fork == 0)
    {
		exec_cmd_redir(tree, mini);
        if (is_a_buildin(tree->cmd->exec_cmd[0]) != 1)
		    execute_cmd(tree, mini->envp);
        if (is_a_buildin(tree->cmd->exec_cmd[0]) == 1)
            exec_buildin_child(tree, mini);
    }
    else
    {
        close(tree->cmd->fd[1]);
        ret = read(tree->cmd->fd[0], buf, 10);
        buf[ret] = '\0';
        close(tree->cmd->fd[0]);
        if (ft_strcmp(buf, "false") == 0)
            tree->cmd->exec = -1;
        while(wait(NULL) != -1)
                ;
    }
    return ;
}
