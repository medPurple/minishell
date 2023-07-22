/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:08:46 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 18:06:32 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
