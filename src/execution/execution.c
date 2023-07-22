/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:50 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 16:33:50 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_cmd_norme(t_binary *tree, int i);

void	exec_recu(t_minishell *mini, t_binary *tree)
{
	if (tree->parentheses == true && tree->cmd_cr == 0)
		return (expand_parentheses_and_execute (tree, mini));
	else if (tree->parentheses == true && tree->cmd_cr == 1
		&& tree->cmd && (tree->cmd->exec == 1 || tree->cmd->exec == -1))
		return ;
	else if (tree->parentheses == false && tree->right)
	{
		exec_recu(mini, tree->left);
		exec_recu(mini, tree->right);
	}
	else
	{
		if (ft_strlen(tree->data) == 0)
			return ;
		if (is_a_meta(tree->data, 0))
			exec_meta(tree, mini);
		else
		{
			if (tree->cmd->exec == 1 || tree->cmd->exec == -1)
				return (exec_recu_norme (mini, tree, 1));
			else
				exec_recu_norme (mini, tree, 2);
		}
	}
	return ;
}

void	execution(t_minishell *mini, t_binary *tree)
{
	int	i;

	i = 0;
	if (ft_strlen(tree->data) == 0)
		return ;
	tree->cmd->check_pipe = -1;
	while (tree->cmd->split_cmd[i])
	{
		if (tree->cmd->split_cmd[0][0] == '&')
			return (execution_norme(mini, tree, 1));
		if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
		{
			if (pipe_is_valid(tree->cmd->split_cmd) < 0)
				return (mini_error_one(4));
			initialize_pipe_value(tree);
			pipex(tree, mini, 0, 0);
			break ;
		}
		i++;
	}
	if (tree->cmd->check_pipe == -1)
		execution_norme(mini, tree, 2);
	return ;
}

void	exec_send(t_binary *tree, t_minishell *mini, int status, int i)
{
	tree->cmd->exec = 1;
	if (is_here_doc(tree) >= 1)
	{
		i = is_here_doc(tree);
		while (i > 0)
		{
			if (tree->cmd->pipe_tmp)
				close (tree->cmd->pipe_tmp);
			tree->cmd->check_here_doc = 1;
			mini_here_doc(tree->redir->redir_file, tree);
			tree->redir = tree->redir->next;
			i--;
		}
	}
	if ((g_eoat == 130) && tree->cmd->check_here_doc == 1)
	{
		unlink(".tmp");
		return ;
	}
	execution_norme_2(mini, tree, status);
	return (ft_free_tab(tree->cmd->exec_cmd));
}

void	execute_cmd(t_binary *tree, t_minishell *mini)
{
	if (tree->cmd->path_cmd)
		free(tree->cmd->path_cmd);
	tree->cmd->path_cmd = cmd_recuperation(tree->cmd->exec_cmd[0], mini->env);
	if (tree->cmd->path_cmd != NULL)
	{
		if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
			execute_cmd_norme(tree, 1);
	}
	else if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
	{
		tree->cmd->path_cmd = tree->cmd->exec_cmd[0];
		if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
			execute_cmd_norme(tree, 2);
	}
	else
	{
		if (ft_strlen(tree->cmd->exec_cmd[0]) != 0)
		{
			ft_free_tab(tree->cmd->exec_cmd);
			mini_error_one(9);
			exit(127);
		}
		ft_free_tab(tree->cmd->exec_cmd);
		exit (0);
	}
}

static void	execute_cmd_norme(t_binary *tree, int i)
{
	if (i == 1)
	{
		if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
		{
			ft_free_tab(tree->cmd->exec_cmd);
			mini_error_one(8);
			exit(126);
		}
		else
		{
			mini_error_one(9);
			ft_free_tab(tree->cmd->exec_cmd);
			exit(127);
		}
	}
	if (i == 2)
	{
		ft_free_tab(tree->cmd->exec_cmd);
		mini_error_one(11);
		exit(126);
	}
}
