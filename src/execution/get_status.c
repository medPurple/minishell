/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:13:07 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/17 14:33:32 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*jap_s(char *bf, char *af);

char	*get_status(t_binary *tree)
{
	int		i;
	int		j;
	char	*bf;
	char	*af;

	bf = NULL;
	af = NULL;
	i = 0;
	while (tree->data[i] && tree->data[i] != '$')
		i++;
	if (i != 0)
		bf = ft_limited_strdup(tree->data, 0, i - 1);
	i += 2;
	j = i;
	while (tree->data[i])
		i++;
	af = ft_limited_strdup(tree->data, j, i);
	return (jap_s(bf, af));
}

static char	*jap_s(char *bf, char *af)
{
	char	*str;

	str = ft_strjoat(bf, ft_itoa(g_eoat));
	str = ft_strjoat (str, af);
	return (str);
}
