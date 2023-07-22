/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:14:25 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 18:21:31 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_unset(t_env **env, char **tab)
{
	int		i;
	t_env	*tmp;
	t_env	*tmp2;
	
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
				if ((*env)->prev && (*env)->next)
				{
					(*env)->prev->next = (*env)->next;
					free((*env)->data);
					free((*env)->name);					
					free(*env);
				}
				else if ((*env)->prev == NULL && (*env)->next)
				{
					tmp2 = (*env)->next;
					tmp2->prev = NULL;
					free((*env)->data);
					free((*env)->name);					
					free(*env);
					tmp = tmp2;
				}
				else
				{
					free((*env)->data);
					free((*env)->name);					
					free(*env);
				}
				break ;
			}
			(*env) = (*env)->next;
		}
		(*env) = tmp;
		i++;
	}
}
