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

int main(int ac, char **av, char **envp)
{
    t_vars var;
    (void)ac;
    (void)av;
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (ft_strncmp(line,"exit",4) == 0)
            return(EXIT_SUCCESS);
        parse_command(line,envp);
        ft_printf("--- %s\n",line);

    }
	return(0);
}
