/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:57:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 11:51:25 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*path_recuperation(t_env *env);
static char	*join_path(char *str, char *path);

void	create_cmd(t_binary *tree)
{
	tree->cmd = malloc(sizeof(t_cmd));
	tree->cmd->exec = 0;
	tree->cmd->str = tree->data;
	tree->cmd->split_cmd = mini_split(tree->data, 0, 0, 0);
	tree->cmd->path_cmd = NULL;
	tree->cmd->exec_cmd = NULL;
	tree->cmd->is_a_redir = 0;
}

char	*cmd_recuperation(char *str, t_env *env)
{
	char	**path;
	int		i;
	char	*cmd;

	i = 0;
	path = NULL;
	if (env != NULL)
		path = ft_split(path_recuperation(env), ':');
	while (path[i])
	{
		cmd = join_path(str, path[i]);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

static char	*path_recuperation(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (tmp->data + 5);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*join_path(char *str, char *path)
{
	path = ft_strjoin(path, "/");
	str = ft_strjoin(path, str);
	return (str);
}

void	ft_free_lst(t_redirection *stack)
{
	t_redirection	*tmp;

	if (!stack)
		return ;
	while (stack)
	{
		tmp = (stack)->next;
		free (stack);
		(stack) = tmp;
	}
	free (stack);
}
