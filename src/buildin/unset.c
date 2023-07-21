/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:14:25 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 07:57:45 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_unset(t_env **env, char **tab)
{
	int		i;
	t_env	*tmp;

	tmp = (*env);
	i = 1;
	if (tab[i][0] == '-')
		return (mini_error_one(15));
	while (tab[i])
	{
		if (ft_strlen(tab[i]) == 0)
			mini_error_one(14);
		while ((*env))
		{
			if (ft_strcmp(tab[i], (*env)->name) == 0)
			{
				(*env)->prev->next = (*env)->next;
				free((*env));
				break ;
			}
			(*env) = (*env)->next;
		}
		(*env) = tmp;
		i++;
	}
}
