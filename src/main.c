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

static void minishell(char *str, t_env *env, char **envp);

int main(int ac, char **av, char **envp)
{
	(void)ac, 
	(void)av;
	char *str;
	t_env	*env;

	env = NULL;
	add_env(&env, envp);
	while (1){
		str = readline("minishell$ ");
		if (ft_strcmp(str,"exit")==0)
			break;

		add_history(str);
		minishell(str, env,envp);
	}
	printf("MINISHELL EXIT\n");

	return(0);
}

static void minishell(char *str, t_env *env, char **envp)
{
	t_env *tmp;
	//int i = 0;
	(void)envp;

	if (ft_strcmp(str,"env")==0)
	{
		tmp = env;
		while(env != NULL)
		{
			ft_printf("%s\n",env->data);
			env = env->next;
		}
		env = tmp;
	}
	else if (ft_strncmp(str,"export ",7)==0)
		mini_export(env,str);
	else
		ft_printf("---%s\n", str);
}