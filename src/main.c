/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/24 16:12:40 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_eoat = 0;

static int	minishell(char *str, t_minishell *mini);

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
		if (minishell(str, &mini) == 0)
			clear_the_tree(mini.tree);
	}
	return (g_eoat);
}

static int	minishell(char *str, t_minishell *mini)
{
	if (parsing(mini, str) == -1)
	{
		if (mini->tree->right)
		{
			clear_the_tree_bis(mini->tree);
			return (-1);
		}
		else
		{
			free(mini->tree->data);
			free(mini->tree);
			return (-1);
		}
	}
	exec_recu(mini, mini->tree);
	return (0);
}
