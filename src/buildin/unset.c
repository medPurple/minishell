/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:14:25 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 16:14:36 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_unset(t_env **env);

void	mini_unset(t_env **env, char **tab, int i, t_env *tmp)
{
	while (tab[i])
	{
		if (ft_strlen(tab[i]) == 0)
			mini_error_one(14);
		while ((*env))
		{
			if (ft_strcmp(tab[i], (*env)->name) == 0)
			{
				if ((*env)->prev && (*env)->next)
					(*env)->prev->next = (*env)->next;
				else if ((*env)->prev == NULL && (*env)->next)
				{
					tmp = (*env)->next;
					tmp->prev = NULL;
				}
				else if ((*env)->prev && (*env)->next == NULL)
					(*env)->prev->next = NULL;
				free_unset(env);
				break ;
			}
			(*env) = (*env)->next;
		}
		(*env) = tmp;
		i++;
	}
}

static void	free_unset(t_env **env)
{
	free((*env)->data);
	free((*env)->name);
	free(*env);
}
