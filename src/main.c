/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/04/05 14:09:25 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void minishell(char *str);

int main(int ac, char **av, char **envp)
{
	(void)ac, (void)av;
	(void)envp;
	char *str;


	while (1){
		str = readline("minishell$ ");
		if (ft_strcmp(str,"exit")==0)
			break;
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