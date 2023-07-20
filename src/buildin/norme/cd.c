/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:58:33 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/20 15:31:00 by wmessmer         ###   ########.fr       */
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
		if (opendir((const char *)path) != NULL)
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
		if (opendir((const char *)str) != NULL)
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
		if (opendir((const char *)path) != NULL)
			changedir(path, env);
		else
			mini_error_one(11);
	}
}
