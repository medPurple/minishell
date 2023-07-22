/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_recu_par.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:33 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 17:10:04 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	exec_recu_par_norme(t_binary *tree);
static void	exec_norme_par(t_binary *tree, t_minishell *mini);

void	exec_recu_par(t_minishell *mini, t_binary *tree)
{
	if (tree->parentheses == true && tree->data[0] == '(')
		expand_parentheses_and_execute(tree, mini);
	else if (tree->right)
	{
		exec_recu_par(mini, tree->left);
		exec_recu_par(mini, tree->right);
	}
	else
	{
		if (ft_strlen(tree->data) == 0)
			return ;
		if (is_a_meta(tree->data, 0))
			exec_meta(tree, mini);
		else
		{
			if (tree->cmd->exec == 1 || tree->cmd->exec == -1)
				return (exec_recu_par_norme(tree));
			else
				exec_norme_par(tree, mini);
		}
	}
	return ;
}

static void	exec_recu_par_norme(t_binary *tree)
{
	if (tree->prev->par_base == 0 \
	&& tree->prev->prev->left->parentheses == false \
	&& ft_strcmp(tree->prev->prev->left->data, "||" ) == 0)
		ft_free_tab(tree->cmd->split_cmd);
	else if (tree->prev->par_base == 0 \
	&&tree->prev->left->parentheses == false \
	&& ft_strcmp(tree->prev->left->data, "||") == 0)
		ft_free_tab(tree->cmd->split_cmd);
}

static void	exec_norme_par(t_binary *tree, t_minishell *mini)
{
	if (tree->status == true)
		tree->cmd->split_cmd = \
		mini_split(get_status(tree), 0, 0, 0);
	execution(mini, tree);
}
