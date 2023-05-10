/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/10 16:22:56 by mvautrot         ###   ########.fr       */
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
			return(i);
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

int	is_a_metacharacters(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	//if (ft_strcmp(str, "(") && ft_strcmp(str, ")"))
	while (str[i])
	{
		if (str[i] == '(')
		{
			while (str[i])
			{
				if (str[i] == ')')
					return(cpt);
				cpt++;
				i++;
			}
		}
		i++;
	}
	return(0);
}
