/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:58:41 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/23 18:57:03 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	mini_here_doc_norme(t_binary *tree, int i)
{
	if (i == 1)
	{
		close (tree->cmd->pipe_tmp);
	}
	else
	{
		send_error("minishell: warning: \
			here-document delimited by end-of-file\n");
		unlink(".tmp");
		close(tree->cmd->pipe_tmp);
		if (tree->cmd->check_pipe == 1)
		{
			close(tree->cmd->pipe_fd[1]);
			close(tree->cmd->pipe_fd[0]);
		}
		exit(0);
	}
}
