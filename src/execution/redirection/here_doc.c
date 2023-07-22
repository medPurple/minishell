/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:25 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/22 16:03:26 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	set_signal_action(void);
static void	sigint_handler(int signal);
static void	op_hd(t_binary *tree);

static void	op_hd(t_binary *tree)
{
	tree->cmd->pipe_tmp = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tree->cmd->pipe_tmp == -1)
		perror ("open");
}

void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;

	line = NULL;
	op_hd(tree);
	set_signal_action();
	if (g_eoat == 130)
		return (mini_here_doc_norme(tree, 0));
	while (1)
	{
		if (g_eoat == 130)
			return (mini_here_doc_norme(tree, 1));
		line = readline(">");
		if (line == NULL)
			mini_here_doc_norme(tree, 2);
		if (strcmp (line, limiter) == 0)
		{
			close(tree->cmd->pipe_tmp);
			return (free(line));
		}
		write (tree->cmd->pipe_tmp, line, ft_strlen(line));
		write (tree->cmd->pipe_tmp, "\n", 1);
		free (line);
	}
}

static void	set_signal_action(void)
{
	struct sigaction	act;

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
