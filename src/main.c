/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/31 16:56:47 by wmessmer         ###   ########.fr       */
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

	mini.env = NULL;
	add_env(&mini.env, envp);
	while (1){
		str = readline("minishell$ ");
		if (ft_strcmp(str,"exit")==0)
			break;
		add_history(str);
		if (ft_strcmp(str,"") != 0)
			minishell(str, &mini);
	}
	printf("MINISHELL EXIT\n");

	return(0);
}

static void minishell(char *str, t_minishell *mini)
{
	t_env *tmp;

	if (ft_strcmp(str,"env")==0)
	{
		tmp = mini->env;
		while(mini->env->next != NULL)
		{
			ft_printf("%s\n",mini->env->data);
			mini->env = mini->env->next;
		}
		ft_printf("%s\n",mini->env->data);
		mini->env = tmp;
	}
	else if (ft_strncmp(str,"export ",7)==0)
		mini_export(mini->env,str);
	else
	{
		parsing(mini,str);
		execution(mini->tree, mini->env);
	}
}
