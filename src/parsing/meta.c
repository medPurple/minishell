/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:58:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/05/30 15:22:32 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_a_meta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	else
		return (false);
}


