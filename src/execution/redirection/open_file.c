/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:31 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/13 11:41:44 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	open_file_bis(t_binary *tree, t_redirection *tmp);
static void	open_file_pipe_bis(t_binary *tree, t_redirection *tmp);
static int	redir_control(t_binary *tree, t_redirection *tmp,
				int pipe, int choice);

static void	open_file_bis(t_binary *tree, t_redirection *tmp)
{
	if (tree->cmd->in)
		close(tree->cmd->in);
	if (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
		tree->cmd->in = open(tmp->redir_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>'))
		tree->cmd->in = open(tmp->redir_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	open_file(t_binary *tree)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	tree->cmd->in = 0;
	tree->cmd->out = 0;
	while (tmp && (redir_is_valid (tmp->redir_file) == 0))
	{
		if ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
			|| (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')))
		{
			open_file_bis(tree, tmp);
			if (check_open (tree->cmd->in) == -1)
				break ;
		}
		if (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
		{
			tree->cmd->out = open (tmp->redir_file, O_RDONLY, 0644);
			if (check_open (tree->cmd->out) == -1)
				break ;
		}
		tmp = tmp->next;
	}
	if (tmp && redir_is_valid (tmp->redir_file) < 0)
		tree->cmd->check_redir = -2;
}

static void	open_file_pipe_bis(t_binary *tree, t_redirection *tmp)
{
	if (tree->cmd->pipe_fd[1])
		close (tree->cmd->pipe_fd[1]);
	if (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
		tree->cmd->pipe_fd[1] = open (tmp->redir_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>'))
		tree->cmd->pipe_fd[1] = open (tmp->redir_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	open_file_pipe(t_binary *tree, int read, int write)
{
	t_redirection	*tmp;

	tmp = tree->redir;
	while (tmp && (redir_is_valid(tmp->redir_file) == 0))
	{
		if (tmp && (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] != '<'))
		{
			tree->cmd->pipe_tmp = open(tmp->redir_file, O_RDONLY, 0644);
			if (redir_control(tree, tmp, read, 1) == -1)
				break ;
		}
		if ((tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] != '>'))
			|| (tmp && (tmp->redir_cmd[0] == '>' && tmp->redir_cmd[1] == '>')))
		{
			if (tree->cmd->check > 0)
				break ;
			open_file_pipe_bis(tree, tmp);
			if (redir_control(tree, tmp, write, 2) == -1)
				break ;
		}
		tmp = tmp->next;
	}
	redir_control(tree, tmp, 0, 0);
	return ;
}

static int	redir_control(t_binary *tree, t_redirection *tmp,
			int pipe, int choice)
{
	if (choice == 0)
	{
		if (tmp && redir_is_valid(tmp->redir_file) < 0)
			tree->cmd->check_redir = -2;
		if (tree->cmd->check > 0)
			perror ("open");
	}
	else
	{
		if (check_open(tree->cmd->pipe_tmp) == -1)
		{
			if (choice == 1)
				tree->cmd->pipe_tmp = pipe;
			else
				tree->cmd->pipe_fd[1] = pipe;
			tree->cmd->check++;
			return (-1);
		}
	}
	return (0);
}
