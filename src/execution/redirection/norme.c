/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:58:41 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/23 13:48:49 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	mini_here_doc_norme(t_binary *tree, int i)
{
	if (i == 0)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (i == 1)
	{
		unlink(".tmp");
		close (tree->cmd->pipe_tmp);
	}
	else
	{
		send_error("minishell: warning: \
			here-document delimited by end-of-file\n");
		unlink(".tmp");
		close(tree->cmd->pipe_tmp);
		exit(0);
	}
}
