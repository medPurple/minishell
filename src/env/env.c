/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:25:35 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 16:42:14 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_env_norme(t_env **env);

void	add_env(t_env **env, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!envp[i])
	{
		add_env_norme(env);
		return ;
	}
	while (envp[i])
	{
		tmp = ft_new_element(ft_strdup(envp[i]));
		ft_add_back_lst(env, tmp);
		i++;
	}
	return ;
}

static void	add_env_norme(t_env **env)
{
	char	*pwd;
	t_env	*tmp;

	pwd = NULL;
	ft_printf("/!\\ No environnement set /!\\\n");
	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin(ft_strdup("PWD="), ft_strdup(pwd));
	tmp = ft_new_element(pwd);
	ft_add_back_lst(env, tmp);
	tmp = ft_new_element(ft_strdup("SHLVL=1"));
	ft_add_back_lst(env, tmp);
	tmp = ft_new_element(ft_strdup("_=/usr/bin/env"));
	ft_add_back_lst(env, tmp);
}
