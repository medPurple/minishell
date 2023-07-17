/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:03:13 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/17 13:50:16 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	has_quotes(char *str);

int	pass_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

int	end_of_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] != c && str[i] != '\0')
		i++;
	while ((str[i] != '&' && str[i + 1] != '&') \
		&& (str[i] != '|' && str[i + 1] != '|') && str[i] != '\0')
	{
		if ((str[i] == '\'') || (str[i] == '\"'))
			i = pass_quotes(str, i);
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

char	**removes_quotes(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (has_quotes(tab[i]))
			tab[i] = rmq_norme(tab[i]);
		i++;
	}
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
