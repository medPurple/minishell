/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:37:04 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/23 13:50:28 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_the_tree(t_binary *tree);
void	clear_env(t_env *env);

void	mini_exit(t_minishell *mini, char *str, t_binary *tree)
{
	if (str)
		g_eoat = ft_atoi(str);
	ft_free_tab(tree->cmd->exec_cmd);
	ft_free_tab(tree->cmd->split_cmd);
	clear_the_tree(mini->tree);
	clear_env(mini->env);
	clear_history();
	exit(g_eoat);
}

void	clear_the_tree(t_binary *tree)
{
	if (tree->right)
	{
		clear_the_tree(tree->left);
		clear_the_tree(tree->right);
	}
	if (!tree->right && ft_strcmp(tree->data, "||") != 0
		&& ft_strcmp(tree->data, "&&") != 0)
		free(tree->cmd);
	free(tree->data);
	tree->prev = NULL;
	tree->right = NULL;
	tree->left = NULL;
	free(tree);
}

void	clear_the_tree_bis(t_binary *tree)
{
	if (tree->right)
	{
		clear_the_tree_bis(tree->left);
		clear_the_tree_bis(tree->right);
	}
	free(tree->data);
	tree->prev = NULL;
	tree->right = NULL;
	tree->left = NULL;
	free(tree);
}

void	clear_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->data);
		free(env->name);
		free(env);
		env = next;
	}
	return ;
}
