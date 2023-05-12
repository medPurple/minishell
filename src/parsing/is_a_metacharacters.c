/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_metacharacters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/12 12:58:02 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//https://abs.traduc.org/abs-5.0-fr/ch05.html

/*seules les commandes builtin ne doivent pas etre interpretees en tant que commande */
/* lorsqu'une commande est executee avec des metacaracteres celle ci ne fonctionne pas
	exemple : ls D* //lol
	=> gerer les metacaracteres lorsqu ils sont entre quotes
	=> gerer les metacaracteres tout court avant non ? enfin non, trop de bruit, a revoir
	pcq la je suis perdue*/

/* CREER UNE FONCTION META QUI REDIRIGE POUR TOUS LES METAS*/

int	search_data(char *str, t_env *env)
{
	int	i;
	int j;
	int	size_data;

	size_data = -1;
	j = 0;
	i = 0;


	//size_data = search_command(str, env);
	/*if (search_command(str, env) != -1)
		size_data = search_command(str, env);
	else if (str[i] == '\'' || str[i] == '\"' || str[i] == '(' || str[i] == '&' || str[i] == '&')
	{
		if (is_a_metacharacters(str) != 0)
			size_data = is_a_metacharacters(str);
	}
	else
		size_data = -1;
	return(size_data);
	if (size_data == -1)
	{*/
	while(str[i])
	{
			// si je croise une commande j'arrete;
		/*if (str[i] == '\'' || str[i] == '\"' || str[i] == '(' || str[i] == '&' || str[i] == '&')
		{*/
		if (is_a_metacharacters(str, env) != 0)
		{
			size_data = is_a_metacharacters(str, env);
			if (size_data != 0)
				return(size_data);
		}
		else if (search_command(str, env) != -1)
		{
			size_data = search_command(str, env);
				return(size_data);
		}
		i++;

	}
	return(size_data);
}
int	is_a_metacharacters(char *str, t_env *env)
{
	int	i;
	int	j;
	int	parenthesis;
	int quotes;

	i = 0;
	j = ft_strlen(str);
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
		if (str[i] == '&' || str[i] == '|')
		{
			if (is_and_else(str) == 1)
			{
				ft_printf ("salut\n");
				return (1);
			}
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
				if (is_a_fonction(str, env) != 0)
					return(j);
				j++;
			}
		}
		i++;
	}
	return(0);
}

int	is_and_else(char *str)
{
	int	i;
	int	check_and;
	int	check_else;

	check_and = 0;
	check_else = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '&')
			check_and++;
		if (str[i] == '|')
			check_else++;
		if (check_and == 2 || check_else == 2)
			return(i);
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
