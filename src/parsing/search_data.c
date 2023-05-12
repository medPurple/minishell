/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:19 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/12 16:18:27 by mvautrot         ###   ########.fr       */
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

int search_command(char *str, t_env *env)
{
    int i;
    int j;
    char *cmd;

    i = 0;
    while (str[i] != '\0' )
    {
        j = 0;
       if (i == 0)
        {
            while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
                i++;
        }
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
        {
            i++;
            j++;
        }
        cmd = malloc ((sizeof (char) * j + 1));
        i = i - j;
        j = 0;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
        {
            cmd[j] = str[i];
            i++;
            j++;
        }
        cmd[j] = '\0';
        if ((is_a_fonction(cmd, env) == 1 || is_a_characters(cmd) != 0))
        {
            free(cmd);
            return (i - j - 1);
        }
        free(cmd);
    }
    return (-1);
}
