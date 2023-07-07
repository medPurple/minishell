/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/07 16:00:56 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void minishell(char *str, t_minishell *mini);

int main(int ac, char **av, char **envp)
{
	(void)ac,
	(void)av;
	char *str;
	t_minishell 	mini;

	str = NULL;
	mini.env = NULL;
	mini.envp = envp;
	add_env(&mini.env, envp);
	while (1)
	{
		signal(SIGINT, signal_ctrlc); // gestion signal ctl c + afficher nvl ligne
		signal(SIGQUIT, SIG_IGN); /* permet d ignorer signal SIGQUIT: ctl+\*/
		str = readline("minishell$ ");
		add_history(str);
		if (str == NULL)
			exit(0);
		minishell(str, &mini);
		clear_the_tree(mini.tree);
	}
	return(0);
}

static void minishell(char *str, t_minishell *mini)
{
	if (parsing(mini,str) == -1)
		return;
	exec_recu(mini, mini->tree);
}
