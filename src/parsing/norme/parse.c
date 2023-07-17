/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:49:58 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/17 11:54:38 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ipp_norme(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] == ' ' && str[i] == '\t' && str[i] != '\0')
		i++;
	return (i);
}

int	ipp_norme_2(char *str, int i)
{
	while (str && (str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
		i++;
	return (i);
}