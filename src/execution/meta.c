/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:54 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/12 16:30:34 by mvautrot         ###   ########.fr       */
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
		ft_printf("error meta\n");
}

void	mini_or(t_binary *tree, t_minishell *mini)
{
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
