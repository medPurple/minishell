/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:53:55 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/24 12:38:27 by wmessmer         ###   ########.fr       */
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

int	verif_meta_norme(t_binary *tree)
{
	if (!tree->prev)
		return (mini_error_one(25), -1);
	if (!tree->prev->right || only_space(tree->prev->right->data) == true)
		return (mini_error_one(25), -1);
	else if ((ft_strcmp(tree->prev->right->data, "&&") == 0 \
	|| ft_strcmp(tree->prev->right->data, "||") == 0))
		return (mini_error_one(25), -1);
	return (0);
}

bool	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			break ;
	}
	if (i == (int)ft_strlen(str))
		return (true);
	else
		return (false);
}
