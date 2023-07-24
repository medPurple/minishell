/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:57:00 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/24 16:33:16 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*path_recuperation(t_env *env);
static char	*join_path(char *str, char *path);

void	create_cmd(t_binary *tree)
{
	if (ft_strcmp(tree->data, "||") != 0 && ft_strcmp(tree->data, "&&") != 0 \
	&& (tree->data[0] != '('))
	{
		tree->cmd = malloc(sizeof(t_cmd));
		tree->cmd->exec = 0;
		tree->cmd->str = ft_strdup(tree->data);
		tree->cmd->split_cmd = NULL;
		tree->cmd->split_cmd = mini_split(ft_strdup(tree->data), 0, 0, 0);
		free(tree->cmd->str);
		tree->cmd->path_cmd = NULL;
		tree->cmd->exec_cmd = NULL;
		tree->cmd->pipe_tmp = 0;
		tree->cmd->is_a_redir = 0;
		tree->cmd->check_here_doc = 0;
		tree->cmd->in = 0;
		tree->cmd->out = 0;
	}
}

char	*cmd_recuperation(char *str, t_env *env)
{
	char	**path;
	int		i;
	char	*cmd;
	char	*pathok;

	if (str && str[0] == '/')
		return (str);
	pathok = path_recuperation(env);
	i = 0;
	path = NULL;
	if (str == NULL || pathok == NULL)
		return (NULL);
	if (env != NULL)
		path = ft_split(path_recuperation(env), ':');
	while (path[i])
	{
		cmd = join_path(str, path[i]);
		if (access(cmd, 0) == 0)
			pathok = ft_strdup(cmd);
		free(cmd);
		i++;
	}
	free(path);
	return (pathok);
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
	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free (tmp->redir_cmd);
		free (tmp->redir_file);
		free (tmp);
	}
}
