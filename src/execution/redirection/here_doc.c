#include "../../../include/minishell.h"
//static void	dup2_fd(int fd, int fd2);
static void	ft_pipe_initialize(t_binary *tree);
static void	ft_gestion_parent(t_binary *tree);

static void	ft_pipe_initialize(t_binary *tree)
{
	//if (pipe(tree->cmd->pipe_fd) == -1)
	//	return;
	tree->cmd->fork = fork();
	if (tree->cmd->fork == -1)
		return;
}

void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;
	ft_pipe_initialize(tree);
	if (tree->cmd->fork == 0)
	{
		while (1)
		{
			line = readline(">");
			if (strcmp(line, limiter) == 0)
			{
				free(line);
				close(tree->cmd->pipe_fd[0]);
				close(tree->cmd->pipe_fd[1]);
				exit(EXIT_SUCCESS);
			}
			write(tree->cmd->pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
		ft_gestion_parent(tree);
}

static void	ft_gestion_parent(t_binary *tree)
{
	int status;

	//tree->cmd->pipe_tmp = tree->cmd->pipe_fd[0];
	//dup2_fd(tree->cmd->pipe_tmp, STDIN_FILENO);
	close(tree->cmd->pipe_fd[1]);
	waitpid(tree->cmd->fork, &status, 0);
	if (WEXITSTATUS(status) > 0)
        tree->cmd->exec = -1;
	else
		 tree->cmd->exec = 1;
}

//static void	dup2_fd(int fd, int fd_redir)
//{
//	if (dup2(fd, fd_redir) < 0)
//		return;
//}

int	is_here_doc(t_binary *tree)
{
	t_redirection	*tmp;
	int	count;

	if (tree->cmd->is_a_redir == 0)
		return(0);
	tmp = tree->redir;
	count = 0;
	while(tmp)
	{
		if (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] == '<')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
