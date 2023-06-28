/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:01 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/23 16:44:51 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
static bool parentheses_success(t_binary *tree);

void expand_parentheses_and_execute(t_binary *tree, t_minishell *mini)
{
	int i;

	i = 0;
	tree->parentheses = false;
	i = ft_strlen(tree->data);
	while(tree->data[i] == ' ' || tree->data[i] == '\t'|| tree->data[i] == '\0')
		i--;
	if (i != end_of_parentheses(tree->data, 0) - 1)
		ft_printf("error token\n");
	else{
		tree->data = ft_limited_strdup(tree->data,1,i - 1);
		if (tree->data == NULL)
		{
			tree->cmd = malloc(sizeof(t_cmd));
			tree->cmd->exec = 0;
			tree->cmd->exec = -1;
		}
		else
		{
			parse_data(tree, mini->env);
			create_cmd_in_tree(tree,mini);
			create_cmd(tree,mini->env);
			exec_recu(mini, tree);
			if (parentheses_success(tree) == true)
				tree->cmd->exec = 1;
			else
				tree->cmd->exec = -1;
		}
		return;
	}
}

static bool parentheses_success(t_binary *tree)
{
	t_binary *tmp;

	tmp = tree;
	while(tmp->right)
		tmp = tmp->right;
	if (tmp->cmd->exec == 1)
		return true;
	else
		return false;
}