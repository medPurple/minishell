/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:14:40 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/22 16:29:52 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../include/minishell.h"

int	fns_norme(char *str, int i)
{
	if (str[i] == '&' || str[i] == '|')
	{
		while (str[i] && (str[i] == '&' || str[i] == '|'))
			i++;
		return (i);
	}
	while (str[i] != '\0' && str[i] != ' ' \
			&& str[i] != '\t')
	{
		if (str[i] == '&' || str[i] == '|')
			return (i);
		if (str[i] == '\'' || str[i] == '\"')
			i = end_of_quotes(str, i);
		else
			i++;
	}
	return (i);
}

int	norme_sp(int i, char *str, int j)
{
	if (j == 0)
	{
		while (str[i] && (str[i] == '&' || str[i] == '|'))
			i++;
	}
	else
	{
		while (str[i] && (str[i] == '&' || str[i] == '|'))
			i--;
	}
	return (i);
}
