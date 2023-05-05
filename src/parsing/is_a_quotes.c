/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/05 14:31:17 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*seules les commandes builtin ne doivent pas etre interpretees en tant que commande */
/* lorsqu'une commande est executee avec des metacaracteres celle ci ne fonctionne pas
	exemple : ls D* //lol*/

int	is_a_quotes(char *str)
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
			return(1);
		i++;
	}
	return(0);
}
