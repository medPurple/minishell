/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:24 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 12:00:21 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_arg(char **tab);
static char	*find_dir(t_env *env);

void	mini_cd(t_env *env, t_binary *tree)
{
	char	*str;
	int		i;

	str = getcwd(NULL, 0);
	if (count_arg(tree->cmd->split_cmd) > 2)
		mini_error_one(16);
	else
	{
		if (count_arg(tree->cmd->split_cmd) == 1)
			changedir(find_dir(env), env);
		else
		{
			i = ft_strlen(str);
			if (ft_strcmp(tree->cmd->split_cmd[1], "..") == 0)
				cd_norme(str, env);
			else
				cd_norme_2(str, tree->cmd->split_cmd[1], env);
		}
	}
}

static int	count_arg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char	*find_dir(t_env *env)
{
	const char	*str;
	t_env		*tmp;

	str = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "HOME") == 0)
			return (ft_limited_strdup(tmp->data, 5, ft_strlen(tmp->data)));
		tmp = tmp->next;
	}
	mini_error_one(17);
	return (NULL);
}

void	changedir(char *destination, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	chdir(destination);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			tmp->data = ft_strjoat("OLDPWD=", getcwd(NULL, 0));
		}
		tmp = tmp->next;
	}
}
