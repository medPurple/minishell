/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:50 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/20 16:05:26 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execution(t_minishell *mini, t_binary *tree);
static	void	ft_wait(t_binary *tree, int status);

//ls | wc -l << eof | ls << eof | << eof ls

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
			{
				if (tree->status == true)
					tree->cmd->split_cmd = mini_split(get_status(tree), 0, 0, 0);
				execution(mini, tree);
			}
		}
	}
	return ;
}

static void	execution(t_minishell *mini, t_binary *tree)
{
	int	i;

	i = 0;
	if (ft_strlen(tree->data) == 0)
		return ;
	tree->cmd->check_pipe = -1;
	while (tree->cmd->split_cmd[i])
	{
		if (tree->cmd->split_cmd[0][0] == '&')
		{
			g_eoat = 2;
			send_error ("minishell: syntax error near unexpected token '&'\n");
			return ;
		}

		if (is_a_pipe(tree->cmd->split_cmd[i]) == true)
		{
			if (pipe_is_valid(tree->cmd->split_cmd) < 0)
			{
				mini_error_one(4);
				return ;
			}
			initialize_pipe_value(tree);
			pipex(tree, mini, 0, 0);
			break ;
		}
		i++;
	}
	if (tree->cmd->check_pipe == -1)
	{
		cmd_redir_malloc(tree, 0, 0, 0);
		i = analyze_error(tree, 0);
		if (i < 0)
			return ;
		execution_choice(tree, mini);
	}
	return ;
}

void	exec_send(t_binary *tree, t_minishell *mini)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	tree->cmd->exec = 1;
	if (is_here_doc(tree) >= 1)
	{
		i = is_here_doc(tree);
		while (i > 0)
		{
			tree->cmd->check_here_doc = 1;
			mini_here_doc(tree->redir->redir_file, tree);
			i--;
		}
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
	signal(SIGQUIT, SIG_DFL);
	while (wait(&status) != -1)
		;
	g_eoat = status / 256;
	if (WEXITSTATUS(status) > 0)
		tree->cmd->exec = -1;
	if (tree->cmd->in != -1 && tree->cmd->in != 0)
		close(tree->cmd->in);
	if (tree->cmd->out != -1 && tree->cmd->out != 0)
		close(tree->cmd->out);
	if (is_here_doc(tree) >= 1)
		close(tree->cmd->pipe_tmp);
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
			if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
			{
				ft_free_tab(tree->cmd->exec_cmd);
				mini_error_one(8);
				exit(126);
			}
			else
			{
				ft_free_tab(tree->cmd->exec_cmd);
				exit(2);
			}
		}
	}
	else if (ft_strchr(tree->cmd->exec_cmd[0], '/') != NULL)
	{
		tree->cmd->path_cmd = tree->cmd->exec_cmd[0];
		if (execve(tree->cmd->path_cmd, tree->cmd->exec_cmd, mini->envp) == -1)
		{
			ft_free_tab(tree->cmd->exec_cmd);
			mini_error_one(11);
			exit(126);
		}
	}
	else
	{
		if (ft_strlen(tree->cmd->exec_cmd[0])!= 0)
		{
			ft_free_tab(tree->cmd->exec_cmd);
			mini_error_one(9);
			exit(127);
		}
		ft_free_tab(tree->cmd->exec_cmd);
		exit (0);
	}
}
