/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:25 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/18 14:39:44 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_pipe_initialize(t_binary *tree);
static void	ft_gestion_parent(t_binary *tree);

static void	ft_pipe_initialize(t_binary *tree)
{
	if (pipe(tree->cmd->fd) == -1)
		perror("pipe");
	tree->cmd->fork = fork();
	if (tree->cmd->fork == -1)
		perror("fork");
	return ;
}

void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;

	ft_pipe_initialize (tree);
	if (tree->cmd->fork == 0)
	{
		while (1)
		{
			line = readline(">");
			close(tree->cmd->fd[0]);
			if (strcmp (line, limiter) == 0)
			{
				free (line);
				close (tree->cmd->fd[1]);
				exit (EXIT_SUCCESS);
			}
			write (tree->cmd->fd[1], line, ft_strlen(line));
			write (tree->cmd->fd[1], "\n", 1);
			free (line);
		}
	}
	else
		ft_gestion_parent (tree);
}

static void	ft_gestion_parent(t_binary *tree)
{
	int	status;

	if (tree->cmd->check_pipe == 1)
		tree->cmd->pipe_tmp = tree->cmd->fd[0];
	close (tree->cmd->fd[1]);
	waitpid (tree->cmd->fork, &status, 0);
	if (WEXITSTATUS(status) > 0)
		tree->cmd->exec = -1;
	if (tree->cmd->check_pipe != 1)
		close (tree->cmd->fd[0]);
}

int	is_here_doc(t_binary *tree)
{
	int				count;
	t_redirection	*tmp;

	if (tree->cmd->is_a_redir == 0)
		return (0);
	tmp = tree->redir;
	count = 0;
	while (tmp)
	{
		if (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] == '<')
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
