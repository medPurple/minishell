/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:56:08 by wmessmer          #+#    #+#             */
/*   Updated: 2023/06/22 17:31:24 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	search_option(char **str);

void	mini_echo(t_binary *tree)
{
	bool	nl;
	int		i;

	i = 1;
	nl = search_option(tree->cmd->exec_cmd);
	if (nl == false)
		i++;
	while (tree->cmd->exec_cmd[i])
	{
		ft_putstr_fd(tree->cmd->exec_cmd[i]);
		ft_putstr_fd(" ");
		i++;
	}
	if (nl == true)
		ft_putstr_fd("\n");
}

static bool	search_option(char **str)
{
	if (ft_strcmp(str[1], "-n") == 0)
		return (false);
	return (true);
}
