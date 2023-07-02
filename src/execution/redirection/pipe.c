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
	i = 0;
	while (i < count)
	{
		j = malloc_cmd_redir(mini, tree, j) + 1;
		for (int o = 0; tree->cmd->exec_cmd[o]; o++)
			ft_printf("- %s\n", tree->cmd->exec_cmd[o]);
		//check_redir_pipe(tree);
		if (pipe(tree->cmd->pipe_fd) == -1)
			perror("pipe");

		tree->cmd->fork_pipe = fork();
    	if (tree->cmd->fork_pipe == -1)
        	perror("fork");
		else if(tree->cmd->fork_pipe == 0)
    	{

			check_redir_pipe(tree);
			close (tree->cmd->pipe_fd[0]);
			/*if (tree->redir && tree->redir->redir_cmd[0] == '<')
			{
				close(tree->cmd->pipe_tmp);
				if(dup2(tree->cmd->out, STDIN_FILENO) == -1)
					perror("dup2");
				close(tree->cmd->out);
			}
			else*/
			//{ 
				//close (tree->cmd->pipe_fd[0]);
				if(dup2(tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
					perror("dup2");
				close(tree->cmd->pipe_tmp);
			//}
			/*if (tree->redir && tree->redir->redir_cmd[0] == '>')
			{
				//close(tree->cmd->pipe_fd[1]);
				//tree->cmd->pipe_fd[1] = tree->cmd->in;
				//close(tree->cmd->in);
				if (dup2(tree->cmd->in, STDOUT_FILENO) == -1)
					perror("dup2");
				close (tree->cmd->in);
			}
			else
			{*/
				//if (tree->cmd->in != -1)
				//	close(tree->cmd->in);
				if (dup2(tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
					perror("dup2");
				close (tree->cmd->pipe_fd[1]);
			//}
        	execution_choice_pipe(tree, mini);
		}
		else
		{
			/*if(tree->redir && tree->redir->redir_cmd[0] == '>')
			{
				ft_printf("salut\n");
				close(tree->cmd->pipe_fd[0]);
				tree->cmd->pipe_tmp = tree->cmd->in;
				close(tree->cmd->in);
			}
			else*/
			tree->cmd->pipe_tmp = tree->cmd->pipe_fd[0];
			/*if (tree->redir && tree->redir->redir_cmd[0] == '<')
			{
				tree->cmd->pipe_tmp = tree->cmd->out;
				close(tree->cmd->out);
			}*/
			//tree->cmd->pipe_tmp = tree->cmd->pipe_fd[0];
			close (tree->cmd->pipe_fd[1]);
		}
		i++;
	}
	j = malloc_cmd_redir(mini, tree, j);
	ft_printf("coucou\n");
	tree->cmd->fork_pipe = fork();
	if (tree->cmd->fork_pipe == -1)
        	perror("fork");
	if(tree->cmd->fork_pipe == 0)
    {

		tree->cmd->check_pipe = 0;
		check_redir_pipe(tree);
		if (dup2(tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
			ft_perror("dup2hhh");
		close(tree->cmd->pipe_tmp);
		execution_choice_pipe(tree, mini);
	}
	else
	{
		//exit(EXIT_SUCCESS);
		//if (tree->cmd->in != -1)
		//	close(tree->cmd->in);
		close(tree->cmd->pipe_fd[1]);
		close(tree->cmd->pipe_tmp);
		//exit(EXIT_SUCCESS);
	}
	while(wait(NULL) != -1)
                ;
	//exit(EXIT_SUCCESS);
	return;

}



void	pipe_exec(t_binary *tree, t_minishell *mini)
{

	//exec_cmd_redir(tree, mini);
    if (is_a_buildin(tree->cmd->exec_cmd[0]) != 1)
	    execute_cmd_pipe(tree, mini);
	else
    	exec_buildin_child(tree, mini);
}


void execute_cmd_pipe(t_binary *tree, t_minishell *mini)
{
	if (tree->cmd->path_cmd)
		free(tree->cmd->path_cmd);
	tree->cmd->path_cmd = cmd_recuperation(tree->cmd->exec_cmd[0], mini->env);
	if (tree->cmd->path_cmd)
    {
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
