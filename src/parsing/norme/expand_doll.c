/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmessmer <wmessmer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:11:19 by wmessmer          #+#    #+#             */
/*   Updated: 2023/07/19 12:22:46 by wmessmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
static char	*search_in_env(char *var, t_env *env, char *str);
static char *doll_quotes(char *str, int position);

char	*replace_doll_bis(char *str, t_env *env, int position)
{
	int	i;
	char *var;
	int j;

	if (str[position] == '\"' || str[position] == '\'')
		return(doll_quotes(str, position));
	else
	{
		j = 0;
		i = position;
		while (str[i] != ' ' && str[i] != '\0' \
		&& str[i] != '\'' && str[i] != '\"')
			i++;
		var = ft_malloc((i - 1) - position , "char");
		while (position < i)
			var[j++] = str[position++];
		var[j] = '\0';
		return(search_in_env(var, env, str));
	}
}

static char	*search_in_env(char *var, t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		str = sie_norme(tmp, str);
	else
		str = jap_norme_2(str);
	return (str);
}

static char *doll_quotes(char *str, int position)
{
	char *bf;
	char *af;
	
	bf = NULL;
	af = NULL;
	bf = ft_limited_strdup(str, 0, position - 2);
	af = ft_limited_strdup(str, position, ft_strlen(str));
	return (ft_strjoin(bf,af));
}