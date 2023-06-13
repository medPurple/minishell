/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:56:08 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/13 18:35:14 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void mini_echo(t_binary *tree)
{
	bool nl; //boolean new line
	int i;

	i = 1;
	nl = search_option(tree->data, "-n");
	if (nl == false)
		i++;
	while (tree->cmd->split_cmd[i])
	{
		ft_putstr_fd(tree->cmd->split_cmd[i]);
		i++;
	}
	if (nl == true)
		ft_putstr_fd("\n");	
}

static bool search_option(char *str, char *opt)
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