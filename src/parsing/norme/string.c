/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:14:40 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/12 16:16:49 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../../include/minishell.h"

int	fns_norme(char *str, int i)
{
	while (str[i] != '\0' && str[i] != ' ' \
			&& str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = end_of_quotes(str, i);
		else
			i++;
	}
	return (i);
}
