/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:32:17 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/12 14:17:04 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*sie_norme(t_env *tmp, char *str)
{
	int		i;
	int		j;
	char	*add;

	j = 0;
	i = 0;
	add = NULL;
	while (tmp->data[i] != '=')
			i++;
	i++;
	add = ft_malloc((ft_strlen(tmp->data) - i), "char");
	while (tmp->data[i] != '\0')
		add[j++] = tmp->data[i++];
	add[j] = '\0';
	str = join_all_part(str, add);
	return (str);
}

char	*jap_norme(char *str, int i, char *before, char *add)
{
	int		j;
	char	*after;

	after = NULL;
	j = 0;
	after = ft_malloc((ft_strlen(str) - i), "char");
	while (str[i] != '\0')
		after[j++] = str[i++];
	after[j] = '\0';
	free(str);
	str = ft_strjoin(before, add);
	str = ft_strjoin(str, after);
	return (str);
}
