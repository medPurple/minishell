/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:08:46 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/23 17:10:26 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void mini_env(t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	while(tmp != NULL)
	{
		ft_printf("%s\n",tmp->data);
		tmp = tmp->next;
	}

}