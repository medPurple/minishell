/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:53:55 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 16:57:37 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	and_norme(t_binary *tree)
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

void	or_norme(t_binary *tree)
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
