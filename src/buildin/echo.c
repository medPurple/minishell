/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:56:08 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 16:40:51 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static bool search_option(char *str);

void mini_echo(t_binary *tree)
{
	bool nl; //boolean new line
	int i;

	i = 1;
	nl = search_option(tree->data);
	if (nl == false)
		i++;
	while (tree->cmd->exec_cmd[i])
	{
		ft_putstr_fd(tree->cmd->exec_cmd[i]);
		i++;
	}
	if (nl == true)
		ft_putstr_fd("\n");
}

static bool search_option(char *str)
{
	char **tab;

	tab = ft_split(str, ' ');
	if (ft_strcmp(tab[1], "-n") == 0)
	{
		ft_free_tab(tab);
		return (false);
	}
	ft_free_tab(tab);
	return(true);
}
