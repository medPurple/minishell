/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:56:32 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/15 13:43:24 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	is_a_characters(char *str, int limit)
{
	int	i;
	int	check_characters;

	i = 0;
	if (limit == -1)
		limit = ft_strlen(str);
	check_characters = 0;
	while (i < limit)
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



