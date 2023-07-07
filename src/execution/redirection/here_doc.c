#include "../../../include/minishell.h"
void	dup2_fd(int fd, int fd2);
static void	ft_pipe_initialize(t_binary *tree);
static void	ft_gestion_parent(t_binary *tree);

static void	ft_pipe_initialize(t_binary *tree)
{
	//if (tree->cmd->check_pipe == -1)
	//{
		if (pipe(tree->cmd->fd) == -1)
			perror("pipe");
	//}
	tree->cmd->fork = fork();
	if (tree->cmd->fork == -1)
		perror("fork");
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
			close(tree->cmd->fd[0]);
			if (strcmp(line, limiter) == 0)
			{
				free(line);
				close(tree->cmd->fd[1]);
				exit(EXIT_SUCCESS);
			}
			write(tree->cmd->fd[1], line, ft_strlen(line));
			write(tree->cmd->fd[1], "\n", 1);
			free(line);
		}
	}
	else
		ft_gestion_parent(tree);
}

static void	ft_gestion_parent(t_binary *tree)
{
	int status;

	close(tree->cmd->fd[1]);
	waitpid(tree->cmd->fork, &status, 0);
	if (WEXITSTATUS(status) > 0)
        tree->cmd->exec = -1;
}


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
