/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:54 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 16:06:47 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_meta( t_binary *tree, t_minishell *mini)
{
	if (ft_strcmp(tree->data, "||") == 0)
		mini_or(tree, mini);
	else if (ft_strcmp(tree->data, "&&") == 0)
		mini_and(tree, mini);
	else
	{
		if (tree->data[0] == '&')
			mini_error_one (10);
		else
			mini_error_one (5);
	}
}

void	mini_or(t_binary *tree, t_minishell *mini)
{
	if (!tree->prev)
	{
		mini_error_one (5);
		return ;
	}
	if (tree->prev->prev->left->cmd->exec == 1)
	{
		if (tree->prev->right->right)
			tree->prev->right->left->cmd->exec = 1;
		else
			tree->prev->right->cmd->exec = 1;
		return ;
	}
	else
		exec_recu(mini, tree->prev->right);
}

void	mini_and(t_binary *tree, t_minishell *mini)
{
	if (!tree->prev)
	{
		mini_error_one (10);
		return ;
	}
	if (tree->prev->prev->left->cmd->exec == -1)
	{
		if (tree->prev->right->right)
			tree->prev->right->left->cmd->exec = -1;
		else
			tree->prev->right->cmd->exec = -1;
		return ;
	}
	else
		exec_recu(mini, tree->prev->right);
}
