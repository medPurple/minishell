/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:54 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 17:02:17 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_meta_par( t_binary *tree, t_minishell *mini)
{
	if (ft_strcmp(tree->data, "||") == 0)
		mini_or_par(tree, mini);
	else if (ft_strcmp(tree->data, "&&") == 0)
		mini_and(tree, mini);
}

void	mini_or_par(t_binary *tree, t_minishell *mini)
{
	if (tree->prev == NULL || tree->prev->prev == NULL)
		return (mini_error_one (5));
	if (tree->prev->prev->left->cmd->exec == 1)
	{
		if (tree->prev->right->right)
			par_or_norme(tree);
		else
		{
			if (tree->prev->right->parentheses == false)
				tree->prev->right->cmd->exec = 1;
			else
			{
				tree->prev->right->cmd = malloc(sizeof(t_cmd));
				tree->cmd_cr = 1;
				tree->prev->right->cmd->exec = 1;
			}
		}
		return ;
	}
	else
		exec_recu_par(mini, tree->prev->right);
	free(tree->data);
}

void	mini_and_par(t_binary *tree, t_minishell *mini)
{
	if (tree->prev == NULL || tree->prev->prev == NULL)
	{
		mini_error_one (10);
		return ;
	}
	if (tree->prev->prev->left->cmd->exec == -1)
	{
		if (tree->prev->right->right)
			par_and_norme(tree);
		else
		{
			if (tree->prev->right->parentheses == false)
				tree->prev->right->cmd->exec = -1;
			else
			{
				tree->prev->right->cmd = malloc(sizeof(t_cmd));
				tree->cmd_cr = 1;
				tree->prev->right->cmd->exec = -1;
			}
		}
		return ;
	}
	else
		exec_recu_par(mini, tree->prev->right);
}
