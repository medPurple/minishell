/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:37:04 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 15:06:15 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_the_tree(t_binary *tree);
void	clear_env(t_env *env);

void	mini_exit(t_minishell *mini, char *str)
{
	if (str)
		g_eoat = ft_atoi(str);
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
	free(tree->rest);
	if (tree->command)
		free(tree->command);
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
		free(env);
		env = next;
	}
	return ;
}
