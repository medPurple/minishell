/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/04/21 14:51:33 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void minishell(char *str);

int main(int ac, char **av, char **envp)
{
	(void)ac, 
	(void)av;
	char *str;
	t_env	env;

	while (1){
		str = readline("minishell$ ");
		if (ft_strcmp(str,"exit")==0)
			break;
		add_env(&env, envp);
		add_history(str);
		minishell(str);
	}
	printf("MINISHELL EXIT\n");

	return(0);
}

static void minishell(char *str)
{
	ft_printf("---%s\n", str);
}