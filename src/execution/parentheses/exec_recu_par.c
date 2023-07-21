/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_recu_par.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:33 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 15:28:08 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_recu_par(t_minishell *mini, t_binary *tree)
{
	if (tree->parentheses == true)
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
			{
				ft_printf("ICI %s\n", tree->data);
				if (tree->prev->par_base == 0 \
				&& tree->prev->prev->left->parentheses == false \
				&& ft_strcmp(tree->prev->prev->left->data, "||" ) == 0)
					ft_free_tab(tree->cmd->split_cmd);
				else if (tree->prev->par_base == 0 \
				&&tree->prev->left->parentheses == false \
				&& ft_strcmp(tree->prev->left->data, "||") == 0)
					ft_free_tab(tree->cmd->split_cmd);
				return ;
			}
			else
			{
				if (tree->status == true)
					tree->cmd->split_cmd = \
					mini_split(get_status(tree), 0, 0, 0);
				execution(mini, tree);
			}
		}
	}
	return ;
}