/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:56 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 13:49:59 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	word_nb(char *str, int i, int count);
static int	after_quotes(char *str, int i);
static int	minisplit_bis(char *str, int i);

char	**mini_split(char *str, int j, int i, int k)
{
	char	**cmd;

	cmd = ft_malloc2(word_nb(str, 0, 0), "char*");
	while (str && str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|')
			&& is_a_redir_or_pipe(str, i, i + 4) > 0)
		{
			j = i;
			i = i + is_a_redir_or_pipe(str, i, i + 4);
			cmd[k++] = ft_limited_strdup(str, j, i - 1);
		}
		else
		{
			j = i;
			i = minisplit_bis(str, i);
			if (i == j)
				break ;
			cmd[k++] = ft_limited_strdup(str, j, i - 1);
		}
	}
	cmd[k] = NULL;
	return (removes_quotes(cmd));
}

static int	minisplit_bis(char *str, int i)
{
	while ((str[i] != ' ' && str[i] != '\t') && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = after_quotes(str, i);
		if ((str[i] == '<' || str[i] == '>' || str[i] == '|')
			&& (is_a_redir_or_pipe(str, i, i + 4) > 0))
		{
			if (str[i - 1] != ' ' && str[i - 1] != '\t')
				break ;
		}
		i++;
	}
	return (i);
}

static int	after_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	word_nb(char *str, int i, int count)
{
	while (str && str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t') && str[i])
			i++;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		{
			count++;
			while ((str[i] != ' ' && str[i] != '\t') && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = after_quotes(str, i);
				if ((str[i] == '<' || str[i] == '>' || str[i] == '|')
					&& (is_a_redir_or_pipe(str, i, i + 4) > 0))
				{
					count++;
					i = i + is_a_redir_or_pipe(str, i, i + 4);
					break ;
				}
				i++;
			}
		}
	}
	return (count);
}
