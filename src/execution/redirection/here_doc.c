/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:25 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/20 16:04:08 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


//static	bool handle_c(char *line);
static void	sign_test(int signal);


void	mini_here_doc(char *limiter, t_binary *tree)
{
	char	*line;

	if (tree->cmd->pipe_tmp != 0 && tree->cmd->pipe_tmp != -1)
		close (tree->cmd->pipe_tmp);
	tree->cmd->pipe_tmp = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	//signal(SIGINT, SIG_IGN);
	signal(SIGINT, sign_test);
		ft_printf("hola\n");
	if (g_eoat == 60)
			ft_printf("EHHHHH\n");
	while (1)
	{
		line = readline(">");

		//signal(SIGINT, sign_test);
		//if (handle_c(line) == true)
		//	return ;
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

/*static	bool handle_c(char *line)
{
	//signal(sig, SIG_IGN);
	if (sig == SIGINT)
		ft_printf("ouh\n");
	ft_printf ("SALUT\n");
	return ;
}*/
static void	sign_test(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("salut !!!!\n");
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_eoat = 60;
		return ;
	}
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
	return (count);
}
