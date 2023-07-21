/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:56:08 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/21 07:54:50 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	search_option(char **str);
static bool	is_ok(char *str);
static int	s_op(char **tab);

void	mini_echo(t_binary *tree)
{
	bool	nl;
	int		i;

	nl = search_option(tree->cmd->exec_cmd);
	i = s_op(tree->cmd->exec_cmd);
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
	if (is_ok(str[1]) == true)
		return (false);
	else
		return (true);
}

static bool	is_ok(char *str)
{
	int		i;
	int		count;
	size_t	n;

	i = 0;
	n = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '-')
			count++;
		if (str[i] == 'n')
			n++;
		i++;
	}
	if (count > 1)
		return (false);
	else if (str && str[0] == '-' && count == 1 && n == (ft_strlen(str) - 1))
		return (true);
	else
		return (false);
}

static int	s_op(char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (is_ok(tab[i]) == true)
			i++;
		else
			break ;
	}
	if (i == 1)
		return (1);
	else
		return (i - 1);
}