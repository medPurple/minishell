/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:03:13 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 15:05:56 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	has_quotes(char *str);

int	pass_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	if (!str[i + 1])
		return (i);
	i++;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

int	end_of_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] != '\0' && str[i] != c)
		i++;
	while (str && str[i] != '\0' && str[i + 1] \
	&& str[i + 1] != '\0' && (str[i] != '&' && str[i + 1] != '&') \
	&& (str[i] != '|' && str[i + 1] != '|'))
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
		{
			i = pass_quotes(str, i) + 1;
			break ;
		}
		else
			i++;
	}
	return (i);
}

int	find_next_quotes(char *str, int pos)
{
	pos++;
	while (str[pos] != '\0')
	{
		if (str[pos] == '\"')
			return (pos);
		pos++;
	}
	return (-1);
}

char	**removes_quotes(char **tab, t_binary *tree)
{
	int		i;
	char	*str;

	i = 0;
	tree->cmd->split_quotes = 0;
	while (tab && tab[i])
	{
		if (has_quotes(tab[i]))
		{
			tree->cmd->split_quotes = tree->cmd->split_quotes * 10 + i;
			str = rmq_norme(tab[i]);
			free(tab[i]);
			tab[i] = ft_strdup(str);
			free(str);
		}
		i++;
	}
	if (tree->cmd->split_quotes == 0)
		tree->cmd->split_quotes = -1;
	return (tab);
}

static bool	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}
