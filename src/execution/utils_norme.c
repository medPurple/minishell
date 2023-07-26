/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:58:21 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/26 17:17:14 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verif_redir_norme(t_binary *tree)
{
	if (tree->right)
	{
		if (verif_redir(tree->left, 0, 0, 0) == -1)
			return (-1);
		if (verif_redir(tree->right, 0, 0, 0) == -1)
			return (-1);
	}
	return (0);
}

t_redirection	*search_h_d(t_redirection *tmp)
{
	while (tmp && ft_strcmp(tmp->redir_cmd, "<<") != 0)
		tmp = tmp->next;
	return (tmp);
}

void	wait_norme_bs(t_binary *tree)
{
	if (tree->cmd->in != -1 && tree->cmd->in != 0)
		close(tree->cmd->in);
	if (tree->cmd->out != -1 && tree->cmd->out != 0)
		close(tree->cmd->out);
	if (tree->cmd->check_here_doc == 1)
	{
		close(tree->cmd->pipe_tmp);
		unlink(".tmp");
	}
	return ;
}

bool	need_spec(int i, int exclude)
{
	while (exclude > 9)
	{
		if (i == exclude % 10)
			return (false);
		else
			exclude = exclude % 10;
	}
	if (i == exclude)
		return (false);
	return (true);
}
