#include "../../include/minishell.h"

int	count_pipe(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;


	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '|')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
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
		pipe_redir(mini, tree);
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


void	pipe_redir(t_minishell *mini, t_binary *tree)
{
	(void)mini;
	close(tree->cmd->fd[0]);
	if(tree->cmd->in)
	{
		if(dup2(tree->cmd->in, STDIN_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if(dup2(tree->cmd->fd[0], STDIN_FILENO))
			perror("dup2");
	}
	if (tree->cmd->out)
	{
		if(dup2(tree->cmd->out, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if(dup2(tree->cmd->fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	if(tree->cmd->in)
		close(tree->cmd->in);
	else
		close(tree->cmd->fd[0]);
	return;
}
