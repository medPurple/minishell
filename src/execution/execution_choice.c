/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_choice.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:47 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/12 11:56:48 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execution_choice(t_binary *tree, t_minishell *mini)
{
	if (is_a_buildin(tree->cmd->exec_cmd[0]) > 0)
		exec_buildin(tree, mini);
	if ((count_redir_right(tree) >= 1) || (count_redir_right_double(tree) >= 1)
		|| (count_redir_left(tree) >= 1) || is_here_doc(tree) >= 1)
	{
		open_file(tree);
		if (check_open(tree->cmd->in) == -1 || check_open(tree->cmd->out) == -1
			|| tree->cmd->open_ko < 0)
		{
			perror("open");
			return ;
		}
		else
			exec_send(tree, mini);
	}
	else
		exec_send(tree, mini);
	return ;
}

void	execution_choice_pipe(t_binary *tree, t_minishell *mini)
{
	if (is_a_buildin(tree->cmd->exec_cmd[0]) == 1)
	{
		exec_buildin(tree, mini);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (is_a_buildin(tree->cmd->exec_cmd[0]) == 0)
			execute_cmd(tree, mini);
		else
			exec_buildin_child(tree, mini);
	}
	return ;
}
