/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_metacharacters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:55:07 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/16 14:11:38 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_metacharacters(char *str, t_env *env, int limit)
{
	int	i;
	int	parenthesis;
	int quotes;

	i = 0;
	parenthesis = 0;
	quotes = 0;
	if (limit == -1)
		limit = ft_strlen(str);
	while (i < limit)
	{
		if (str[i] == '(')
		{
			parenthesis = is_a_parenthesis(str);
			if (parenthesis != 0)
				return (parenthesis);
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = is_a_quotes(str, env);
			if (quotes != 0)
				return(quotes);
		}
		i++;
	}
	return(0);
}

int	is_a_quotes(char *str, t_env *env) // rajouter * et $ ?
{
	(void)env;
	int	i;
	int	j;
	int	check_single;
	int	check_double;

	check_single = 0;
	check_double = 0;
	i = 0;
	j = 0;
	if (/*str[0] != '\'' && */str[0] != '\"')
	{
		while (str[i] != '\"' /*||  str[i] != '\''*/)
			i++;
		return(i - 1);
	}
	else
	{
		while (str[i] != '\"')
		{
			/*if (str[i] == '\'')
				check_single++;*/
			if (str[i] == '\"')
				return (i);
				//
				//check_double++;
			/*if ((str[i] == '\'' && check_single != 2) || (str[i] == '\"' && check_double != 2))
			{
				return (i);
				//if (str[i] == '|' || str[i] == '&' || str[i] == '>' || str[i] == '<')
			}*/
		i++;
		}

	}
	return(0);
}

int	is_a_parenthesis (char *str)
{
	int	i;
	int	check_parenthesis;

	i = 0;
	check_parenthesis = 0;
	if (str[0] == '(')
	{
		while (str[i])
		{
			if (str[i] == '(')
				check_parenthesis++;
			if (str[i] == ')' && check_parenthesis != 2)
				return (i);
			i++;
		}
	}
	else
	{
		while (str[i] != '(')
			i++;
		return(i - 1);
	}
	return (0);
}
