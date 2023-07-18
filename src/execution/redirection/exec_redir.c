/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:22 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/18 14:20:30 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_cmd_redir(t_binary *tree)
{
	if (count_redir_right(tree) >= 1 || count_redir_right_double(tree) >= 1)
	{
		if (dup2(tree->cmd->in, STDOUT_FILENO) == -1)
			perror("dup2");
		close(tree->cmd->in);
	}
	if (count_redir_left(tree) >= 1)
	{
		if (dup2(tree->cmd->out, STDIN_FILENO) == -1)
			perror("dup2");
		close(tree->cmd->out);
	}
	if (is_here_doc(tree) >= 1)
	{
		if (dup2(tree->cmd->fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(tree->cmd->fd[0]);
	}
	return ;
}

void	check_redir_pipe(t_binary *tree)
{
	if ((count_redir_right(tree) >= 1) || (count_redir_right_double(tree) >= 1)
		|| (count_redir_left(tree) >= 1))
		open_file_pipe(tree, tree->cmd->pipe_tmp, tree->cmd->pipe_fd[1]);
	return ;
}
