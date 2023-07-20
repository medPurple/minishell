/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:03:01 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 16:59:18 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**path_recuperation(t_env *env);
static int	test_path(char *str, char **path);

int	is_a_buildin(char *str)
{
	if ((ft_strcmp(str, "cd") == 0) || (ft_strcmp(str, "export") == 0) \
		|| (ft_strcmp(str, "unset") == 0) || (ft_strcmp(str, "exit") == 0))
		return (1);
	if ((ft_strcmp(str, "echo") == 0) || (ft_strcmp(str, "pwd") == 0) \
		|| (ft_strcmp(str, "env") == 0))
		return (2);
	return (0);
}

int	is_a_fonction(char *str, t_env *env)
{
	char	**split_env;
	t_env	*tmp;

	tmp = env;
	split_env = path_recuperation(tmp);
	if (split_env == NULL)
		return (0);
	if (test_path(str, split_env) == 1)
	{
		free(split_env);
		return (1);
	}
	//ft_free_tab(split_env);
	return (0);
}

static char	**path_recuperation(t_env *env)
{
	char	*tmp_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (env == NULL)
		return (NULL);
	while (ft_strcmp(env->name, "PATH") != 0)
	{
		if (env->next == NULL)
			return (NULL);
		env = env->next;
	}
	while (env->data[i] != '=')
		i++;
	tmp_env = malloc(sizeof(char ) * (ft_strlen(env->data) - i));
	i++;
	while (env->data[i])
	{
		tmp_env[j] = env->data[i];
		i++;
		j++;
	}
	tmp_env[j] = '\0';
	return (ft_split(tmp_env, ':'));
}

static int	test_path(char *str, char **path)
{
	int		i;
	char	*join;
	char	*search;

	i = 0;
	while (path[i])
	{
		join = ft_strjoin(path[i], "/");
		search = ft_strjoin(join, str);
		if (access(search, F_OK) == 0)
		{
			free(search);
			return (1);
		}
		free(search);
		i++;
	}
	return (0);
}
