/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_metacharacters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/11 11:55:43 by mvautrot         ###   ########.fr       */
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

int	is_a_metacharacters(char *str)
{
	int	i;
	int	parenthesis;
	int quotes;

	i = 0;
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
		else if (str[i] == '\'' || str[i] == '\"')
		{
			ft_printf("serieusement?");
			quotes = is_a_quotes(str);
			if (quotes != 0)
				return(quotes);
		}
		i++;
	}
	return(0);
}

int	is_a_quotes(char *str) // rajouter * et $ ?
{
	int	i;
	int	check_single;
	int	check_double;

	check_single = 0;
	check_double = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			check_single++;
		if (str[i] == '\"')
			check_double++;
		if (check_single == 2 || check_double == 2)
		{
			ft_printf("QUOTES !\n");
			return(i);
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
	while (str[i])
	{
		if (str[i] == '(')
			check_parenthesis++;
		if (str[i] == ')' && check_parenthesis != 2)
			return (i);
		i++;
	}
	return (0);
}
