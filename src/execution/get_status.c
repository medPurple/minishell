/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:13:07 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/26 12:11:52 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*jap_s(char *bf, char *af);

char	*get_status(char *str)
{
	int		i;
	int		j;
	char	*bf;
	char	*af;

	bf = NULL;
	af = NULL;
	i = 0;
	while (str[i] && str[i + 1] && str[i] != '$' && str[i + 1] != '?')
		i++;
	if (str[i + 1] == '\0')
		return (str);
	if (i != 0)
		bf = ft_limited_strdup(str, 0, i - 1);
	i += 2;
	j = i;
	while (str[i])
		i++;
	af = ft_limited_strdup(str, j, i);
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
		if (af)
		{
			str2 = ft_strjoin(str, af);
			return (free(af), free(str3), str2);
		}
		return (free(str3), str);
	}
	else if (af)
	{
		str2 = ft_strjoin(str3, af);
		return (free(af), str2);
	}
	return (str3);
}

char	*get_all_status(char *str)
{
	int		i;
	char	*str2;

	str2 = NULL;
	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str2 = get_status(str);
			free(str);
			str = ft_strdup(str2);
			free(str2);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}
