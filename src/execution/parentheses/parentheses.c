/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:01 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 17:07:14 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	parentheses_success(t_binary *tree);
static void	expand_utils(t_binary *tree);
static void	expand_utils_bis(t_binary *tree, t_minishell *mini);

void	expand_parentheses_and_execute(t_binary *tree, t_minishell *mini)
{
	int		i;
	char	*str;

	i = 0;
	i = ft_strlen(tree->data);
	while (tree->data[i] == ' ' || tree->data[i] == '\t' \
		|| tree->data[i] == '\0')
		i--;
	str = ft_strdup(tree->data);
	free(tree->data);
	tree->data = ft_limited_strdup(str, 1, i - 1);
	free(str);
	if (tree->cmd_cr == 1)
		return ;
	if (tree->data == NULL || ft_strlen(tree->data) == 0)
	{
		expand_utils(tree);
		return ;
	}
	else
	{
		expand_utils_bis(tree, mini);
	}
}

static void	expand_utils(t_binary *tree)
{
	tree->cmd = malloc(sizeof(t_cmd));
	tree->cmd->exec = -1;
	free(tree->data);
	mini_error_one(20);
	return ;
}

static void	expand_utils_bis(t_binary *tree, t_minishell *mini)
{
	parse_data(tree, mini->env);
	if (tree->right)
	{
		tree->cmd = malloc(sizeof(t_cmd));
		tree->cmd_cr = 1;
		tree->cmd->exec = 0;
		create_cmd_in_tree(tree);
	}
	else
	{
		tree->cmd_cr = 1;
		create_cmd(tree);
	}
	tree->par_base = 1;
	exec_recu_par(mini, tree);
	if (tree->right)
	{
		if (parentheses_success(tree) == true)
			tree->cmd->exec = 1;
		else
			tree->cmd->exec = -1;
	}
}

static bool	parentheses_success(t_binary *tree)
{
	t_binary	*tmp;

	tmp = tree;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->cmd->exec == 1)
		return (true);
	else
		return (false);
}
