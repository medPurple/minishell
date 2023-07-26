/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:13:07 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/25 23:31:26 by wmessmer         ###   ########.fr       */
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
	while (tree->data[i] && tree->data[i + 1] && tree->data[i] != '$' && tree->data[i + 1] != '?')
		i++;
	if (tree->data[i + 1] == '\0')
		return (tree->data);
	if (i != 0)
		bf = ft_limited_strdup(tree->data, 0, i - 1);
	i += 2;
	j = i;
	while (tree->data[i])
		i++;
	af = ft_limited_strdup(tree->data, j, i);
	free(tree->data);
	return (jap_s(bf, af));
}

static char	*jap_s(char *bf, char *af)
{
	char	*str;
	char	*str2;
	char	*str3;

	str = NULL;
	str2 = NULL;
	str3 = NULL;
	str3 = ft_itoa(g_eoat);
	if (bf)
	{
		str = ft_strjoin(bf, str3);
		str2 = ft_strjoat (str, af);
	}
	else
		str2 = ft_strjoat (str3, af);
	free(str3);
	return (str2);
}

char	*get_all_status(t_binary *tree)
{
	int	i;

	i = 0;
	while (tree->data[i] && tree->data[i + 1])
	{
		if (tree->data[i] == '$'&& tree->data[i + 1] == '?')
		{
			tree->data = get_status(tree);
			i = 0;
		}
		else
			i++;
	}
	return (tree->data);
}
