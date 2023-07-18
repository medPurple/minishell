/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/18 15:16:52 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_eoat = 0;

static void	minishell(char *str, t_minishell *mini);

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_minishell	mini;

	if (ac > 1)
	{
		mini_error_one(11);
		return (127);
	}
	(void)av;
	str = NULL;
	mini.env = NULL;
	mini.envp = envp;
	add_env(&mini.env, envp);
	while (1)
	{
		signal(SIGINT, signal_ctrlc);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell$ ");
		add_history(str);
		if (str == NULL)
			exit(g_eoat);
		minishell(str, &mini);
		clear_the_tree(mini.tree);
	}
	return (g_eoat);
}

static void	minishell(char *str, t_minishell *mini)
{
	if (parsing(mini, str) == -1)
		return ;
	exec_recu(mini, mini->tree);
}
