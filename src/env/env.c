/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:25:35 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 07:58:31 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env(t_env **env, char **envp)
{
	int		i;
	t_env	*tmp;
	char	*pwd;

	pwd = NULL;
	i = 0;
	if (!envp[i])
	{
		ft_printf("/!\\ No environnement set /!\\\n");
		pwd = getcwd(NULL, 0);
		pwd = ft_strjoat("PWD=", pwd);
		tmp = ft_new_element(pwd);
		ft_add_back_lst(env, tmp);
		tmp = ft_new_element("SHLVL=1");
		ft_add_back_lst(env, tmp);
		tmp = ft_new_element("_=/usr/bin/env");
		ft_add_back_lst(env, tmp);
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
