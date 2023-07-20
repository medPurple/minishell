/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:25 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/20 18:27:48 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	set_signal_action(void);
static void	sigint_handler(int signal);

void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;

	line = NULL;
	if (tree->cmd->pipe_tmp != 0 && tree->cmd->pipe_tmp != -1)
		close (tree->cmd->pipe_tmp);
	tree->cmd->pipe_tmp = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	set_signal_action();
	if (g_eoat == 130)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	while (1)
	{
		if (g_eoat == 130)
		{
			close (tree->cmd->pipe_tmp);
			return ;
		}
		line = readline(">");
		if (line == NULL)
		{
			send_error("minishell: warning: here-document delimited by end-of-file\n");
			close(tree->cmd->pipe_tmp);
			exit(0);
		}
		if (strcmp (line, limiter) == 0)
		{
			free (line);
			return ;
		}
		write (tree->cmd->pipe_tmp, line, ft_strlen(line));
		write (tree->cmd->pipe_tmp, "\n", 1);
		free (line);
	}
}

static void	set_signal_action(void)
{
	struct sigaction act;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

static void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		g_eoat = 130;

}

int	is_here_doc(t_binary *tree)
{
	int				count;
	t_redirection	*tmp;

	if (tree->cmd->is_a_redir == 0)
		return (0);
	tmp = tree->redir;
	count = 0;
	while (tmp)
	{
		if (tmp->redir_cmd[0] == '<' && tmp->redir_cmd[1] == '<')
		{
			count++;
		}
		tmp = tmp->next;
	}
	g_eoat = 0;
	return (count);
}
