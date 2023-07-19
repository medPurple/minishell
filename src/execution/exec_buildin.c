/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:58 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/19 14:43:40 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_a_num (char *str);
static int	valid_exit(char *str, char *str2);

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
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "exit") == 0
		&& (valid_exit(tree->cmd->exec_cmd[1], tree->cmd->exec_cmd[2]) > 0))
		mini_exit(mini);
}

void	exec_buildin_child(t_binary *tree, t_minishell *mini)
{
	if (ft_strcmp(tree->cmd->exec_cmd[0], "echo") == 0)
		mini_echo(tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "pwd") == 0)
		mini_pwd(mini->env, tree);
	else if (ft_strcmp(tree->cmd->exec_cmd[0], "env") == 0)
		mini_env(mini->env);
	exit(EXIT_SUCCESS);
}

static int	valid_exit(char *str, char *str2)
{
	if (ft_strlen(str) > 0 && is_a_num(str) == 0)
		return (send_error("minishell: exit: numeric argument required\n"), 0);
	else if (is_a_num(str) > 0 && ft_strlen(str2) > 0)
		return (send_error("minishell: exit: too many arguments\n"), 0);
	else
		return(1);
}

static int	is_a_num (char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) > 0)
		{
			g_eoat = ft_atoi(str);
			return (1);
		}
		i++;
	}
	return (0);
}


