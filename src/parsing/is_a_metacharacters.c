/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_metacharacters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:55:07 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/12 16:18:09 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_metacharacters(char *str, t_env *env)
{
	int	i;
	int	characters;
	int	parenthesis;
	int quotes;

	i = 0;
	characters = 0;
	parenthesis = 0;
	quotes = 0;
	while (str[i])
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
	int	i;
	int	j;
	int	check_single;
	int	check_double;

	check_single = 0;
	check_double = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			check_single++;
		if (str[i] == '\"')
			check_double++;
		if (check_single == 2 || check_double == 2)
		{
			j = i;
			while (str[j] != 0)
			{
				if (str[i] == '|' || str[i] == '&' || str[i] == '>' || str[i] == '<')
					return(j- 1);
				else if (is_a_fonction(str, env) != 0)
					return(j);
				j++;
			}
		}
		i++;
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
