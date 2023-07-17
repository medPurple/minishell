/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:58:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/07/17 16:08:52 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_a_meta(char *str, int i)
{
	if (!(str[i + 1]))
		return (false);
	if (str[i] == '|' && str[i + 1] == '|')
		return (true);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (true);
	else
		return (false);
}
