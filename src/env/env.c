/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:25:35 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/12 17:25:36 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env(t_env **env, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		tmp = ft_new_element(ft_strdup(envp[i]));
		ft_add_back_lst(env, tmp);
		i++;
	}
	return ;
}
