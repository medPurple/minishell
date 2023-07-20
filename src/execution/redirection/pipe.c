/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:24:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/20 10:32:49 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	initialize_pipe_value(t_binary *tree)
{
	tree->cmd->check_here_doc = 0;
	tree->cmd->is_a_redir = 0;
	tree->cmd->check_redir = 0;
	tree->cmd->pipe_tmp = 0;
	tree->cmd->check_pipe = 1;
	tree->cmd->status = 0;
	tree->cmd->count = 0;
	tree->cmd->check = 0;
}

int	count_pipe(t_binary *tree)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tree->cmd->split_cmd[i])
	{
		if (is_a_pipe (tree->cmd->split_cmd[i]) == true)
			count++;
		i++;
	}
	return (count);
}

void	pipex(t_binary *tree, t_minishell *mini, int i, int j)
{
	tree->cmd->count = count_pipe(tree);
	while (i < tree->cmd->count)
	{
		if (tree->redir)
			pipe_option(tree, 1, j);
		j = cmd_redir_malloc(tree, j, j, j) + 1;
		pipe_option(tree, 3, j);
		if (tree->cmd->check_redir < 0)
		{
			pipe_option(tree, 1, j);
			return ;
		}
		pipe_reduce(tree);
		if (tree->cmd->fork_pipe == 0)
			fork_option (mini, tree, 1, 0);
		else
		{
			pipe_parent (tree, 1);
			if (tree->cmd->check_redir < 0)
				break ;
		}
		i++;
	}
	if (tree->cmd->check_redir >= 0)
		last_pipex(tree, mini, i, j);
	return ;
}

void	last_pipex(t_binary *tree, t_minishell *mini, int i, int j)
{
	int	k;

	k = 0;
	i = j;
	if (tree->redir)
		pipe_option (tree, 1, j);
	j = cmd_redir_malloc (tree, j, j, j);
	pipe_option(tree, 3, j);
	if (tree->cmd->check_redir < 0)
	{
		pipe_option (tree, 1, j);
		return ;
	}
	if (is_here_doc (tree) >= 1)
	{
		k = is_here_doc (tree);
		while (k > 0)
		{
			tree->cmd->check_here_doc = 1;
			mini_here_doc (tree->redir->redir_file, tree);
			close(tree->cmd->fd[1]);
			k--;
		}
	}
	tree->cmd->fork_pipe = fork();
	if (tree->cmd->fork_pipe == -1)
		perror ("fork");
	if (tree->cmd->fork_pipe == 0)
		fork_option (mini, tree, 0, i);
	else
		pipe_parent (tree, 0);
	wait_child (tree);
	return ;
}

void	wait_child(t_binary *tree)
{
	signal(SIGQUIT, SIG_DFL);
	while (wait(&tree->cmd->status) != -1)
		;
	if (WEXITSTATUS(tree->cmd->status) > 0)
		tree->cmd->exec = -1;
	else
		tree->cmd->exec = 1;
}
