/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:51:58 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/20 14:30:52 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	fork_option_bis(t_minishell *mini, t_binary *tree, int i);

//<< eof | ls | wc -l << eof | ls << eof | wc -l << eof


void	pipe_option( t_binary *tree, int choice, int pos)
{
	int	i;
	int	k;

	i = 0;
	if (choice == 1)
	{
		tree->cmd->is_a_redir = 0;
		ft_free_lst(tree->redir);
		tree->redir = NULL;
	}
	else if (choice == 2)
	{
		k = is_here_doc (tree);
		while (k > 0)
		{
			tree->cmd->check_here_doc = 1;
			mini_here_doc(tree->redir->redir_file, tree);
			//check_redir_pipe(tree); /* UTILITE A VERIFIER  !!!!!!!!!*/
			tree->cmd->is_a_redir = 0;
			k--;
		}
	}
	else
	{
		i = analyze_error(tree, pos);
		if (i < 0)
		{
			tree->cmd->is_a_redir = 0;
			ft_free_lst(tree->redir);
			tree->redir = NULL;
			return ;
		}
	}
}

void	pipe_reduce(t_binary *tree)
{
	if (pipe (tree->cmd->pipe_fd) == -1)
		perror("pipe");
	if (is_here_doc (tree) >= 1)
	{
		pipe_option(tree, 2, 0);
	}
	else
		tree->cmd->check_here_doc = 0;
	tree->cmd->fork_pipe = fork();
	if (tree->cmd->fork_pipe == -1)
		perror ("fork");
}

void	pipe_parent(t_binary *tree, int choice)
{
	if (choice == 1)
	{
		if (tree->cmd->pipe_tmp != -1 && tree->cmd->pipe_tmp != 0)
			close (tree->cmd->pipe_tmp);
		tree->cmd->pipe_tmp = tree->cmd->pipe_fd[0];
		close (tree->cmd->pipe_fd[1]);
	}
	else
	{
		close(tree->cmd->pipe_fd[1]);
		close(tree->cmd->pipe_tmp);
	}
}

void	fork_option(t_minishell *mini, t_binary *tree, int choice, int i)
{
	if (choice == 1)
	{
		if (tree->cmd->is_a_redir == 1)
			check_redir_pipe(tree);
		close (tree->cmd->pipe_fd[0]);
		if (dup2 (tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
				perror("dup2");
		if (dup2 (tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close (tree->cmd->pipe_fd[1]);
		if (tree->cmd->check_redir < 0)
		{
			pipe_option (tree, 3, 0);
			return ;
		}
		else
			execution_choice_pipe (tree, mini);
	}
	else
		fork_option_bis(mini, tree, i);
}

static void	fork_option_bis(t_minishell *mini, t_binary *tree, int i)
{
	tree->cmd->check_pipe = 0;
	if (tree->cmd->is_a_redir == 1)
	{
		check_redir_pipe(tree);
	}
	if (last_pipe_redir(tree, i) > 0)
	{
		if (dup2 (tree->cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close (tree->cmd->pipe_fd[1]);
	}
	if (tree->cmd->check_here_doc == 1 || tree->cmd->check_here_doc == 0)
	{
		if (dup2 (tree->cmd->pipe_tmp, STDIN_FILENO) == -1)
			ft_perror("dup2");
		close (tree->cmd->pipe_tmp);
	}
	execution_choice_pipe (tree, mini);
}

