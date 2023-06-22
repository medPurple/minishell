/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:16:56 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 16:29:50 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
static void	dup2_fd(int fd, int fd2);
static void	ft_gestion_before(t_binary *tree);
static void	ft_gestion_parent(t_binary *tree);

static void	ft_gestion_before(t_binary *tree)
{
	if (pipe(tree->cmd->fd) < 0)
		return;
	tree->cmd->fork = fork();
	if (tree->cmd->fork < 0)
		return;
}

static void	ft_gestion_parent(t_binary *tree)
{
	dup2_fd(tree->cmd->fd[0], STDIN_FILENO);
	tree->cmd->in = tree->cmd->fd[0];
	close(tree->cmd->fd[1]);
	waitpid(tree->cmd->fork, NULL, 0);
}

void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;

	ft_gestion_before(tree);
	if (tree->cmd->fork == 0)
	{
		while (1)
		{
			line = readline(">");
			if (strcmp(line, limiter) == 0)
			{
				free(line);
				close(tree->cmd->fd[0]);
				close(tree->cmd->fd[1]);
				exit(EXIT_SUCCESS);
			}
			write(tree->cmd->fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
		ft_gestion_parent(tree);
}

static void	dup2_fd(int fd, int fd2)
{
	if (dup2(fd, fd2) < 0)
		return;
}