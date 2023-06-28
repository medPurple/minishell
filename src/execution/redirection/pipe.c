#include "../../../include/minishell.h"

static int	count_pipe(t_binary *tree);

static int	count_pipe(t_binary *tree)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tree->cmd->split_cmd[i])
	{
		if(is_a_pipe(tree->cmd->split_cmd[i]) == true)
			count++;
		i++;
	}
	return(count);
}

void	pipe_gestion(t_binary *tree, t_minishell *mini)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;

	count = count_pipe(tree);

	ft_printf ("count : %i\n", count);
	while (i < count)
	{
		j = malloc_cmd_redir(mini, tree, j) + 1;
		for (int k = 0; tree->cmd->exec_cmd[k]; k++)
			ft_printf("- %s",tree->cmd->exec_cmd[k]);
		ft_printf("\n");
		if (pipe(tree->cmd->pipe_fd) == -1)
        	perror("pipe");
    	tree->cmd->fork_pipe = fork();
    	if (tree->cmd->fork_pipe == -1)
        	perror("fork");
		else if(tree->cmd->fork_pipe == 0)
    	{

			pipe_redir(tree);
        	execution_choice(tree, mini);
		}
		else
		{
			close(tree->cmd->pipe_fd[1]);
		}
		i++;
	}
	j = malloc_cmd_redir(mini, tree, j);
	for (int k = 0; tree->cmd->exec_cmd[k]; k++)
		ft_printf("- %s ",tree->cmd->exec_cmd[k]);
	ft_printf("\n");
	tree->cmd->fork_pipe = fork();
	if (tree->cmd->fork_pipe == -1)
        	perror("fork");
	if(tree->cmd->fork_pipe == 0)
    {

		tree->cmd->check_pipe = 0;
		pipe_redir(tree);
		execution_choice(tree, mini);
	}
	else
	{
		close(tree->cmd->pipe_fd[0]);
		close(tree->cmd->pipe_fd[1]);
	}
	while(wait(NULL) != -1)
                ;
	return;

}

void	pipe_redir(t_binary *tree)
{
	if (tree->cmd->check_pipe == 1)
	{
		if(dup2(tree->cmd->pipe_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		if(dup2(tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(tree->cmd->pipe_fd[0]);
		close(tree->cmd->pipe_fd[1]);
	}
	else
	{
		if(dup2(tree->cmd->pipe_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(tree->cmd->pipe_fd[0]);
		//close(tree->cmd->pipe_fd[1]);
	}
	return;
}


void	pipe_exec(t_binary *tree, t_minishell *mini)
{

	exec_cmd_redir(tree, mini);
    if (is_a_buildin(tree->cmd->exec_cmd[0]) != 1)
	    execute_cmd_pipe(tree, mini);
	else
    	exec_buildin_child(tree, mini);
}


void execute_cmd_pipe(t_binary *tree, t_minishell *mini)
{
	if (tree->cmd->path_cmd)
		free(tree->cmd->path_cmd);
	tree->cmd->path_cmd =  cmd_recuperation(tree->cmd->exec_cmd[0], mini->env);
    if (tree->cmd->path_cmd)
    {
        ft_printf("- %s",tree->cmd->path_cmd);
		for (int k = 0; tree->cmd->exec_cmd[k]; k++)
			ft_printf("- %s",tree->cmd->exec_cmd[k]);
		ft_printf("\n");
		if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
        {
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
    {
        tree->cmd->path_cmd = tree->cmd->exec_cmd[0];
        if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
        {
            ft_free_tab(tree->cmd->exec_cmd);
            ft_perror(" Error : Command execution\n");
        }
    }
    else
    {
        ft_free_tab(tree->cmd->exec_cmd);
		ft_perror("path");
    }
    ft_free_tab(tree->cmd->exec_cmd);

}
