/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:37:04 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/25 13:31:20 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_the_tree(t_binary *tree);
void	clear_env(t_env *env);

void	mini_exit(t_minishell *mini, t_binary *tree)
{
	ft_free_tab(tree->cmd->exec_cmd);
	ft_free_tab(tree->cmd->split_cmd);
	clear_the_tree(mini->tree);
	if (mini->env->data == NULL)
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

	if (!env)
		return ;
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
