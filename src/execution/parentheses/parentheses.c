/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:01 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 15:29:17 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	parentheses_success(t_binary *tree);

void	expand_parentheses_and_execute(t_binary *tree, t_minishell *mini)
{
	int	i;

	i = 0;
	char *str;
	i = ft_strlen(tree->data);
	while (tree->data[i] == ' ' || tree->data[i] == '\t' \
		|| tree->data[i] == '\0')
		i--;
	str = ft_strdup(tree->data);
	free(tree->data);
	tree->data = ft_limited_strdup(str, 1, i - 1);
	free(str);
	if (tree->cmd_cr == 1)
		return;
	if (tree->data == NULL || ft_strlen(tree->data) == 0)
	{
		tree->cmd = malloc(sizeof(t_cmd));
		tree->cmd->exec = -1;
		free(tree->data);
		mini_error_one(20);
		return ;
	}
	else
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
		//ft_free_tab(tree->cmd->split_cmd);
	}
}

static bool	parentheses_success(t_binary *tree)
{
	t_binary	*tmp;

	tmp = tree;
	while (tmp->right)
	{
		//if (tree->right && (ft_strcmp(tmp->left->data, "||") != 0) && ft_strcmp(tmp->left->data, "&&") != 0)
		//	free(tmp->left->cmd);
		tmp = tmp->right;
	}
	if (tmp->cmd->exec == 1)
	{
		//free(tmp->cmd);
		return (true);
	}
	else
	{
		//free(tmp->cmd);
		return (false);
	}
}
