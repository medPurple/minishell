/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:58:33 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 17:36:17 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cd_norme(char *str, t_env *env)
{
	int		i;
	char	*path;

	path = NULL;
	if (!str)
		mini_error_one(18);
	else
	{
		i = ft_strlen(str);
		while (str[i] != '/')
			i--;
		if (i == 0)
			path = "/";
		else
			path = ft_limited_strdup(str, 0, i - 1);
		free(str);
		if (open_close(path) == true)
			changedir(path, env, NULL, NULL);
		else
		{
			free(path);
			mini_error_one(11);
		}
	}
}

void	cd_norme_2(char *str, char *cmd, t_env *env)
{
	char	*path;

	path = NULL;
	if (cmd[0] == '/')
	{
		if (open_close(str) == true)
		{
			changedir(cmd, env, NULL, NULL);
			free(str);
		}
		else
			mini_error_one(11);
	}
	else
	{
		path = ft_strjoin(str, "/");
		path = ft_strjoin(path, cmd);
		if (open_close(path) == true)
			changedir(path, env, NULL, NULL);
		else
		{
			free(path);
			mini_error_one(11);
		}
	}
}

bool	open_close(char *str)
{
	DIR	*direction;

	direction = opendir((const char *)str);
	if (direction != NULL)
	{
		closedir(direction);
		return (true);
	}
	return (false);
}

void	cd_norme_3(char *str, t_binary *tree, t_env *env, int j)
{
	if (count_arg(tree->cmd->split_cmd, j) == 1)
		changedir(find_dir(env), env, NULL, NULL);
	else if (ft_strlen(tree->cmd->split_cmd[j + 1]) == 1 \
	&& tree->cmd->split_cmd[j + 1][0] == '-')
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (ft_strlen(tree->cmd->split_cmd[j + 1]) != 1 \
	&& tree->cmd->split_cmd[j + 1][0] == '-')
		mini_error_one(15);
	else
	{
		if (ft_strcmp(tree->cmd->split_cmd[j + 1], "..") == 0)
			cd_norme(str, env);
		else
			cd_norme_2(str, tree->cmd->split_cmd[j + 1], env);
	}
}
