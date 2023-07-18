/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:58 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/18 15:38:37 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

;

void	exec_buildin(t_binary *tree, t_minishell *mini)
{
	tree->cmd->exec = 1;
	g_eoat = 0;
	if (ft_strcmp(tree->cmd->exec_cmd[0], "cd") == 0)
		mini_cd(mini->env, tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "export") == 0)
		mini_export(&mini->env, tree->cmd->exec_cmd);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "unset") == 0)
		mini_unset(&mini->env, tree->cmd->exec_cmd);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "exit") == 0)
		mini_exit(mini);
}

void	exec_buildin_child(t_binary *tree, t_minishell *mini)
{
	if (ft_strcmp(tree->cmd->exec_cmd[0], "echo") == 0)
		mini_echo(tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "pwd") == 0)
		mini_pwd(mini->env);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "env") == 0)
		mini_env(mini->env);
	exit(EXIT_SUCCESS);
}

