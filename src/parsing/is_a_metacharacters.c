/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_metacharacters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/12 15:50:59 by mvautrot         ###   ########.fr       */
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

	while(str[i])
	{
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
		else if (str[i] == '&' || str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if (is_a_characters(str) != 0)
			{
				size_data = is_a_characters(str);
				if (size_data != 0)
					return(size_data);
			}
		}
		i++;

	}
	return(size_data);
}
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
					return(j - 1);
				else if (is_a_fonction(str, env) != 0)
					return(j);
				j++;
			}
		}
		i++;
	}
	return(0);
}

int	is_a_characters(char *str)
{
	int	i;
	int	check_characters;

	i = 0;
	check_characters = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			check_characters = is_a_redirection(str);
		else if (str[i] == '|')
			check_characters = is_a_pipe_or_else(str);
		else if (str[i] == '&')
			check_characters = is_a_and(str);
		i++;
	}
	return (check_characters);
}

int	is_a_redirection(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		return(2);
	else if (str[0] == '>' || str[0] == '<')
		return(1);
	else
	{
		while (str[i] != '>' || str[i] != '<')
			i++;
		return(i - 1);
	}
	return (0);
}

int	is_a_pipe_or_else(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '|' && str[1] == '|'))
		return(2);
	else if ((str[0] == '|' && str[1] != '|'))
		return(1);
	else
	{
		while (str[i] != '|' || str[i] != '|')
			i++;
		return(i - 1);
	}
	return (0);
}

int is_a_and(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '&' && str[1] == '&'))
		return(2);
	else if (str[0] == '&' && str[1] != '&')
		return(0);
	else
	{
		while (str[i] != '&' || str[i] != '&')
			i++;
		return(i - 1);
	}
	return (0);

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
