/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_par_norme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:00:15 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 17:02:56 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	par_and_norme(t_binary *tree)
{
	if (tree->prev->right->left->parentheses == false)
		tree->prev->right->left->cmd->exec = -1;
	else
	{
		tree->prev->right->left->cmd = malloc(sizeof(t_cmd));
		tree->cmd_cr = 1;
		tree->prev->right->left->cmd->exec = 1;
	}
}

void	par_or_norme(t_binary *tree)
{
	if (tree->prev->right->left->parentheses == false)
		tree->prev->right->left->cmd->exec = 1;
	else
	{
		tree->prev->right->left->cmd = malloc(sizeof(t_cmd));
		tree->cmd_cr = 1;
		tree->prev->right->left->cmd->exec = 1;
	}
}
