/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:58:12 by mvautrot          #+#    #+#             */
/*   Updated: 2023/06/15 14:33:01 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_a_meta(char *str, int i)
{
	if (!(str[i + 1]))
		return (false);
	if (str[i] == '|' && str[i+ 1] == '|')
		return (true);
	else if (str[i] == '&' && str[i+1] == '&')
		return (true);
	else
		return (false);
}