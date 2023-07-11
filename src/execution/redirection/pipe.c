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

void	pipex(t_binary *tree, t_minishell *mini)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = count_pipe(tree);
	i = 0;
	tree->cmd->check_here_doc = 0;
	tree->cmd->is_a_redir = 0;
	tree->cmd->open_ko = 0;
	tree->cmd->pipe_tmp  = 0;
	while (i < count)
	{
		if(tree->redir)
		{
			tree->cmd->is_a_redir = 0;
			ft_free_lst(tree->redir);
			tree->redir = NULL;
		}
		j = cmd_redir_malloc(tree, j) + 1;
		if (tree->cmd->open_ko < 0)
		{
			ft_free_tab(tree->cmd->exec_cmd);
			return;
		}
		if (pipe(tree->cmd->pipe_fd) == -1)
			perror("pipe");
		if (is_here_doc(tree) >= 1)
		{
			if (tree->redir->redir_file == NULL)
			{
				tree->cmd->open_ko = -6;
				ft_printf("here_doc\n");
				return;
			}
			tree->cmd->check_here_doc = 1;
			mini_here_doc(tree->redir->redir_file, tree);
			check_redir_pipe(tree);
			tree->cmd->is_a_redir = 0;
		}
		tree->cmd->check_here_doc = 0;
		tree->cmd->fork_pipe = fork();
    	if (tree->cmd->fork_pipe == -1)
        	perror("fork");
		else if(tree->cmd->fork_pipe == 0)
    	{
			if (tree->cmd->is_a_redir == 1)
				check_redir_pipe(tree);
			close (tree->cmd->pipe_fd[0]);
			if(dup2(tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
				perror("dup2");
			if (dup2(tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
				perror("dup2");
			close (tree->cmd->pipe_fd[1]);
			if(tree->cmd->open_ko < 0 )
			{
				ft_free_tab(tree->cmd->exec_cmd);
				return;
			}
			else
				execution_choice_pipe(tree, mini);
		}
		else
		{
			if (tree->cmd->pipe_tmp  != -1 && tree->cmd->pipe_tmp  != 0)
				close (tree->cmd->pipe_tmp);
			tree->cmd->pipe_tmp = tree->cmd->pipe_fd[0];
			close (tree->cmd->pipe_fd[1]);
			if (tree->cmd->open_ko < 0)
				break;
		}
		i++;
	}
	if (tree->cmd->open_ko >= 0)
		last_pipex(tree, mini, i, j);
	return;
}

void    last_pipex(t_binary *tree, t_minishell *mini, int i, int j)
{
	int	status;

	i = j;
	if(tree->redir)
	{
		tree->cmd->is_a_redir = 0;
		ft_free_lst(tree->redir);
		tree->redir = NULL;
	}
	j = cmd_redir_malloc(tree, j);
	if (is_here_doc(tree) >= 1)
	{
		if (tree->redir->redir_file == NULL)
		{
			ft_printf("here_doc\n");
			tree->cmd->open_ko = -6;
			return;
		}
		tree->cmd->check_here_doc = 1;
		mini_here_doc(tree->redir->redir_file, tree);
	}
	tree->cmd->fork_pipe = fork();
	if (tree->cmd->fork_pipe == -1)
       	perror("fork");
	if(tree->cmd->fork_pipe == 0)
    {
		tree->cmd->check_pipe = 0;
		if (tree->cmd->is_a_redir == 1)
			check_redir_pipe(tree);
		if (last_pipe_redir(tree, i) > 0)
		{
			if (dup2(tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
				perror("dup2");
			close (tree->cmd->pipe_fd[1]);
		}
		if (tree->cmd->check_here_doc == 0)
		{
			if (dup2(tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
				ft_perror("dup2");
			close(tree->cmd->pipe_tmp);
		}
		execution_choice_pipe(tree, mini);
	}
	else
	{
		close(tree->cmd->pipe_fd[1]);
		close(tree->cmd->pipe_tmp);
	}
	while(wait(&status) != -1)
                ;
	if (WEXITSTATUS(status) > 0) // pb is possible // maybe need waitpid
        tree->cmd->exec = -1;
	else
		 tree->cmd->exec = 1;
	return;
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
