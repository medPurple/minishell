/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:50 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/13 13:34:01 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execution(t_minishell *mini, t_binary *tree);
static	void	ft_wait(t_binary *tree, int status);

void	exec_recu(t_minishell *mini, t_binary *tree)
{
	if (tree->parentheses == true)
		expand_parentheses_and_execute(tree, mini);
	else if (tree->right)
	{
		exec_recu(mini, tree->left);
		exec_recu(mini, tree->right);
	}
	else
	{
		if (is_a_meta(tree->data, 0))
			exec_meta(tree, mini);
		else
		{
			if (tree->cmd->exec == 1 || tree->cmd->exec == -1)
				return ;
			else
				execution(mini, tree);
		}
	}
	return ;
}

static void	execution(t_minishell *mini, t_binary *tree)
{
	int	i;

	i = 0;
	tree->cmd->check_pipe = -1;
	while (tree->cmd->split_cmd[i])
	{
		if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
		{
			initialize_pipe_value(tree);
			pipex(tree, mini, 0, 0);
			break ;
		}
		i++;
	}
	if (tree->cmd->check_pipe == -1)
	{
		i = cmd_redir_malloc(tree, 0, 0, 0);
		if (i < 0)
		{
			analyze_error(tree);
			ft_printf("error_gestion\n");
			return ;
		}
		execution_choice(tree, mini);
	}
	return ;
}

void	exec_send(t_binary *tree, t_minishell *mini)
{
	int	status;

	status = 0;
	tree->cmd->exec = 1;
	if (is_here_doc(tree) >= 1)
	{
		tree->cmd->check_here_doc = 1;
		mini_here_doc(tree->redir->redir_file, tree);
	}
	tree->cmd->fork = fork();
	if (tree->cmd->fork == -1)
		perror("fork");
	else if (tree->cmd->fork == 0)
	{
		exec_cmd_redir(tree);
		if (is_a_buildin(tree->cmd->exec_cmd[0]) == 0)
			execute_cmd(tree, mini);
		else
			exec_buildin_child(tree, mini);
	}
	else
		ft_wait(tree, status);
	return ;
}

static	void	ft_wait(t_binary *tree, int status)
{
	while (wait(&status) != -1)
		;
	if (WEXITSTATUS(status) > 0)
		tree->cmd->exec = -1;
}

void	execute_cmd(t_binary *tree, t_minishell *mini)
{
	if (tree->cmd->path_cmd)
		free(tree->cmd->path_cmd);
	tree->cmd->path_cmd = cmd_recuperation(tree->cmd->exec_cmd[0], mini->env);
	if (tree->cmd->path_cmd != NULL)
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
}
