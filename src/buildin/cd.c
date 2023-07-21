/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:16:24 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 07:53:27 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_arg(char **tab, int j);
static char	*find_dir(t_env *env);
static int	search_cd(t_binary *tree);

void	mini_cd(t_env *env, t_binary *tree)
{
	char	*str;
	int		j;

	str = getcwd(NULL, 0);
	j = search_cd(tree);
	if (count_arg(tree->cmd->split_cmd, j) > 2)
	{
		if ((count_arg(tree->cmd->split_cmd, j) == 3) \
		&& tree->cmd->split_cmd[j + 2][0] == '/')
			cd_norme_2(str, ft_strjoin(tree->cmd->split_cmd[j + 1], \
			tree->cmd->split_cmd[j + 2]), env);
		else
			mini_error_one(16);
	}
	else
	{
		if (count_arg(tree->cmd->split_cmd, j) == 1)
			changedir(find_dir(env), env);
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
}

static int	search_cd(t_binary *tree)
{
	int	i;

	i = 0;
	while (tree->cmd->split_cmd[i])
	{
		if (ft_strcmp(tree->cmd->split_cmd[i], "cd") == 0)
			return (i);
		i++;
	}
	return (0);
}

static int	count_arg(char **tab, int j)
{
	int	i;

	i = 0;
	while (tab[j] && ft_strcmp(tab[j], "|") != 0)
	{
		i++;
		j++;
	}
	return (i);
}

static char	*find_dir(t_env *env)
{
	t_env		*tmp;

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
	char	*old;
	char	*str;
	char	*dest;

	str = getcwd(NULL, 0);
	old = ft_strdup("OLDPWD=");
	tmp = env;
	if (!destination)
		return ;
	chdir(destination);
	free(destination);
	dest = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->data);
			dest = ft_strjoat(old, str);
			tmp->data = ft_strdup(dest);
			free(dest);
			break ;
		}
		tmp = tmp->next;
	}
	free(str);
}