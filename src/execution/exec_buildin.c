/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:58 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/26 16:14:26 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_a_num(char *str, int i, int count);
static int	valid_exit(char *str, char *str2);

void	exec_buildin(t_binary *tree, t_minishell *mini)
{
	tree->cmd->exec = 1;
	g_eoat = 0;
	if (ft_strcmp(tree->cmd->exec_cmd[0], "cd") == 0)
		mini_cd (mini->env, tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "export") == 0)
		mini_export(&mini->env, tree->cmd->exec_cmd);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "unset") == 0 \
	&& tree->cmd->exec_cmd[1])
	{
		if (tree->cmd->exec_cmd[1][0] == '-')
			mini_error_one(15);
		else
			mini_unset(&mini->env, tree->cmd->exec_cmd, 1, mini->env);
	}
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "exit") == 0)
	{
		if (tree->cmd->exec_cmd[1] && !(tree->cmd->exec_cmd[2]) \
		&& valid_exit(tree->cmd->exec_cmd[1], NULL) > 0)
			mini_exit(mini, tree);
		if (tree->cmd->exec_cmd[1] && tree->cmd->exec_cmd[2] \
		&& valid_exit(tree->cmd->exec_cmd[1], tree->cmd->exec_cmd[2]) > 0)
			mini_exit(mini, tree);
		else if (!(tree->cmd->exec_cmd[1]))
			mini_exit(mini, tree);
	}
}

void	exec_buildin_child(t_binary *tree, t_minishell *mini)
{
	if (ft_strcmp(tree->cmd->exec_cmd[0], "echo") == 0)
		mini_echo(tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "pwd") == 0)
		mini_pwd(mini->env, tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "env") == 0)
		mini_env(mini->env);
	ft_free_tab(tree->cmd->exec_cmd);
	exit(EXIT_SUCCESS);
}

static int	valid_exit(char *str, char *str2)
{
	if (str && ft_strlen(str) > 0 && is_a_num(str, 0, 0) == 0)
		return (send_error("minishell: exit: numeric argument required\n"), 1);
	else if (str && str2 && is_a_num(str, 0, 0) > 0 && ft_strlen(str2) > 0)
		return (send_error("minishell: exit: too many arguments\n"), 0);
	else
		return (1);
}

static int	is_a_num(char *str, int i, int count)
{
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		count++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) > 0)
			count++;
		i++;
	}
	if (count == (int)ft_strlen(str))
	{
		g_eoat = ft_atoi(str);
		return (1);
	}
	g_eoat = 2;
	return (0);
}
