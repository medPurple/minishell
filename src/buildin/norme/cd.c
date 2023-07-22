/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:58:33 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 15:41:26 by wmessmer         ###   ########.fr       */
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
			changedir(path, env);
		else
			mini_error_one(11);
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
			changedir(cmd, env);
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
			changedir(path, env);
		else
			mini_error_one(11);
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